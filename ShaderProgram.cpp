#include "ShaderProgram.h"

#include "Data.h"
#include "GLFWApplication.h"
#include "Mesh.h"
#include "Message.h"
#include "Shader.h"


using namespace gl;

ShaderProgram::ShaderProgram() :
    m_programId(0),
    m_instanced(1),
    m_polygonMode(PolygonMode::FILL),
    m_shaderList(3),
    m_dataList(),
    m_isLinked(false)
{
    m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    for (BaseData* baseData : m_dataList) {
        delete baseData;
        baseData = nullptr;
    }
    glDeleteProgram(m_programId);
}

GLuint ShaderProgram::getProgramID() const
{
    return m_programId;
}

unsigned int ShaderProgram::getNbInstance() const
{
    return m_instanced;
}

void ShaderProgram::setNbInstance(unsigned int instance)
{
    if (instance == 0)
        instance = 1;

    m_instanced = instance;
}

ShaderProgram::PolygonMode ShaderProgram::getPolygonMode() const
{
    return this->m_polygonMode;
}

void ShaderProgram::setPolygonMode(PolygonMode polygonMode)
{
    this->m_polygonMode = polygonMode;
}

bool ShaderProgram::addShader(const Shader& shader)
{
    if (!shader.isCompiled())
        return false;

    typedef Shader::ShaderType ShaderType;
    ShaderType type = shader.getShaderType();

    if (m_shaderList[type] != nullptr) {
        msg_warning("ShaderProgram") << "Shader " << type << " already set in ShaderProgram " << m_programId;
        return false;
    }

    m_shaderList[type] = &shader;

    return true;
}

void ShaderProgram::link()
{
    GLint linked = 0;

    for (const Shader* shader : m_shaderList) {
        if (shader != nullptr)
            glAttachShader(m_programId, shader->getShaderID());
    }

    glLinkProgram(m_programId);

    glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
        msg_error("ShaderProgram") << "Linkage failed: " << infoLog;
    }

    m_isLinked = linked;

    for (const Shader* shader : m_shaderList) {
        if (shader != nullptr)
            glDetachShader(m_programId, shader->getShaderID());
    }
}

bool ShaderProgram::isLinked() const
{
    return m_isLinked;
}

void ShaderProgram::updateDataIfDirty()
{
    for (BaseData* baseData : m_dataList) {
        baseData->updateIfDirty();
    }
}

void ShaderProgram::draw()
{
    GLFWApplication* app = GLFWApplication::getInstance();

    glPolygonMode(GL_FRONT_AND_BACK, this->m_polygonMode);

    // Bind program
    glUseProgram(m_programId);

    // update all inputs shader so we can draw safely
    this->updateDataIfDirty();

    // Draw
    if (m_instanced == 1) {
        app->m_mesh->draw();
    } else {
        app->m_frame->drawInstanced(m_instanced);
    }

    // Unbind program
    glUseProgram(0);
}

int ShaderProgram::attributLocation(const char *name) const
{
    if (!m_isLinked)
        return -1;

    return glGetUniformLocation(this->m_programId, name);
}
