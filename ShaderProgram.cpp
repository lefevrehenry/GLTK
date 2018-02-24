#include "ShaderProgram.h"

#include "GLFWApplication.h"
#include "Mesh.h"
#include "Message.h"
#include "Scene.h"
#include "Shader.h"


using namespace gl;

GLFWApplication* app = GLFWApplication::getInstance();

ShaderProgram::ShaderProgram() :
    m_programId(0),
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

PolygonMode ShaderProgram::getPolygonMode() const
{
    return this->m_drawStyle.polygonMode;
}

void ShaderProgram::setPolygonMode(PolygonMode polygonMode)
{
    this->m_drawStyle.polygonMode = polygonMode;
}

PrimitiveMode ShaderProgram::getPrimitiveMode() const
{
    return this->m_drawStyle.primitiveMode;
}

void ShaderProgram::setPrimitiveMode(PrimitiveMode primitiveMode)
{
    this->m_drawStyle.primitiveMode = primitiveMode;
}

unsigned int ShaderProgram::getNbInstance() const
{
    return this->m_drawStyle.instanced;
}

void ShaderProgram::setNbInstance(unsigned short instance)
{
    if (instance == 0)
        instance = 1;

    this->m_drawStyle.instanced = instance;
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
    Scene* scene = app->getScene();

    // Bind program
    glUseProgram(m_programId);

    // update all inputs shader so we can draw safely
    this->updateDataIfDirty();

    if (scene != nullptr)
        scene->draw(this->m_drawStyle);

    // Unbind program
    glUseProgram(0);
}

int ShaderProgram::attributLocation(const char *name) const
{
    if (!m_isLinked)
        return -1;

    return glGetUniformLocation(this->m_programId, name);
}
