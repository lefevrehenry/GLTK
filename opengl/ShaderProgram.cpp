#include <opengl/ShaderProgram.h>

#include <helper/FileRepository.h>
#include <opengl/Mesh.h>
#include <helper/Message.h>
#include <graph/SceneGraph.h>
#include "Shader.h"
#include <opengl/VisualManager.h>

// Standard Library
#include <fstream>
#include <memory>

using namespace gl;
using namespace gl::helper;

static bool getStringFromFile(const std::string& filename, std::string& dest)
{
    std::ifstream filestream(filename, std::ios::in);

    if(!filestream.is_open()) {
        msg_error("Helper") << "File " << filename << " not found";
        return false;
    }

    dest = "";
    std::string line;

    while(getline(filestream, line)) {
        dest += line + "\n";
    }

    filestream.close();

    return true;
}


ShaderProgram* ShaderProgram::Create(ShaderProgramType shaderProgramType)
{
    typedef Shader::ShaderType ShaderType;

    ShaderProgram* shaderProgram = new ShaderProgram();

    std::string vertexFilename = "";
    std::string geometryFilename = "";
    std::string fragmentFilename = "";

    std::string vs = "";
    std::string gs = "";
    std::string fs = "";

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        vertexFilename = "shaders/basic.vs";
        fragmentFilename = "shaders/basic.fs";

        break;
    case ShaderProgramType::Normal:

        vertexFilename = "shaders/normal.vs";
        geometryFilename = "shaders/normal.gs";
        fragmentFilename = "shaders/normal.fs";

        break;
    case ShaderProgramType::FlatShading:

        vertexFilename = "shaders/flatShading.vs";
        geometryFilename = "shaders/flatShading.gs";
        fragmentFilename = "shaders/flatShading.fs";

        break;
    case ShaderProgramType::GouraudShading:

        vertexFilename = "shaders/gouraudShading.vs";
        fragmentFilename = "shaders/gouraudShading.fs";

        break;
    case ShaderProgramType::PhongShading:

        vertexFilename = "shaders/phongShading.vs";
        fragmentFilename = "shaders/phongShading.fs";

        break;

    case ShaderProgramType::Frame:

        vertexFilename = "shaders/frame.vs";
        fragmentFilename = "shaders/frame.fs";

        break;
    case ShaderProgramType::HighLight:

        vertexFilename = "shaders/highLight.vs";
        geometryFilename = "shaders/highLight.gs";
        fragmentFilename = "shaders/highLight.fs";

        break;
    case ShaderProgramType::BasicTexturing:

        vertexFilename = "shaders/basicTexturing.vs";
        fragmentFilename = "shaders/basicTexturing.fs";

        break;
    case ShaderProgramType::Texturing:

        vertexFilename = "shaders/texturing.vs";
        fragmentFilename = "shaders/texturing.fs";

        break;
    case ShaderProgramType::TangentSpace:

        vertexFilename = "shaders/tangentSpace.vs";
        geometryFilename = "shaders/tangentSpace.gs";
        fragmentFilename = "shaders/tangentSpace.fs";

        break;
    case ShaderProgramType::Picking:

        vertexFilename = "shaders/picking.vs";
        fragmentFilename = "shaders/picking.fs";

        break;
    case ShaderProgramType::OutLine:

        vertexFilename = "shaders/outline.vs";
        fragmentFilename = "shaders/outline.fs";

        break;
    case ShaderProgramType::MatCap:

        vertexFilename = "shaders/matcap.vs";
        fragmentFilename = "shaders/matcap.fs";

        break;
    case ShaderProgramType::VaoQuad:

        vertexFilename = "shaders/vaoQuad.vs";
        fragmentFilename = "shaders/vaoQuad.fs";

        break;
    case ShaderProgramType::Deferred:

        vertexFilename = "shaders/deferred.vs";
        fragmentFilename = "shaders/deferred.fs";

        break;
    case ShaderProgramType::ShadowMapping:

        vertexFilename = "shaders/shadowMapping.vs";
        fragmentFilename = "shaders/shadowMapping.fs";

        break;
    case ShaderProgramType::NormalMapping:

        vertexFilename = "shaders/normalMapping.vs";
        fragmentFilename = "shaders/normalMapping.fs";

        break;
    case ShaderProgramType::CubeMap:

        vertexFilename = "shaders/cubeMap.vs";
        fragmentFilename = "shaders/cubeMap.fs";

        break;
    case ShaderProgramType::EnvironmentMapping:

        vertexFilename = "shaders/environmentMapping.vs";
        fragmentFilename = "shaders/environmentMapping.fs";

        break;
    }

    if (DataRepository.findFile(vertexFilename))
        getStringFromFile(vertexFilename, vs);

    if (DataRepository.findFile(geometryFilename))
        getStringFromFile(geometryFilename, gs);

    if (DataRepository.findFile(fragmentFilename))
        getStringFromFile(fragmentFilename, fs);

    if (vs != "") {
        vertexShader.compileSourceCode(vs);
        shaderProgram->addShader(vertexShader);
    }

    if (gs != "") {
        geometryShader.compileSourceCode(gs);
        shaderProgram->addShader(geometryShader);
    }

    if (fs != "") {
        fragmentShader.compileSourceCode(fs);
        shaderProgram->addShader(fragmentShader);
    }

    shaderProgram->link();

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Normal:

        shaderProgram->addData<float>("scale", 0.5f);
        shaderProgram->addData<glm::vec3>("normalColor", glm::vec3(1,1,1));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::FlatShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::GouraudShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::PhongShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Frame:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);
        shaderProgram->setNbInstance(3);

        break;
    case ShaderProgramType::HighLight:

        shaderProgram->addData<glm::vec3>("color", glm::vec3(1.0,0.8,0.0));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->set<CullFace>(GL_TRUE);
        shaderProgram->set<DepthMask>(GL_FALSE);
        shaderProgram->set<DepthFunc>(GL_LESS);

        break;
    case ShaderProgramType::BasicTexturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Texturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::TangentSpace:

        shaderProgram->setPrimitiveType(PrimitiveType::POINTS);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Picking:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::OutLine:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::MatCap:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::VaoQuad:

        break;
    case ShaderProgramType::Deferred:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::ShadowMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::NormalMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::CubeMap:

        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->set<CullFace>(GL_FALSE);
        shaderProgram->set<DepthFunc>(GL_LEQUAL);

        break;
    case ShaderProgramType::EnvironmentMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    }

    return shaderProgram;
}

ShaderProgram::ShaderProgram() :
    m_programId(0),
    m_shaderList(3),
    m_dataList(),
    m_isLinked(false),
    m_nbInstance(1),
    m_primitiveType(TRIANGLES),
    m_attributeStack()
{
    m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    for (auto it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        BaseData* baseData = it->second;
        delete baseData;
        baseData = nullptr;
    }
    glDeleteProgram(m_programId);
}

GLuint ShaderProgram::getProgramID() const
{
    return this->m_programId;
}

unsigned int ShaderProgram::getNbInstance() const
{
    return this->m_nbInstance;
}

void ShaderProgram::setNbInstance(unsigned int n)
{
    this->m_nbInstance = n;
}

PrimitiveType ShaderProgram::getPrimitiveType() const
{
    return this->m_primitiveType;
}

void ShaderProgram::setPrimitiveType(PrimitiveType primitiveType)
{
    this->m_primitiveType = primitiveType;
}

template< AttributeName N >
void PushAndApply(BaseOpenGLAttribut::SPtr baseAttribut)
{
    typename OpenGLAttribut<N>::SPtr attribut = std::static_pointer_cast< OpenGLAttribut<N> >(baseAttribut);

    OpenGLStateMachine::Push<N>();
    OpenGLStateMachine::Set<N>(*attribut);
}

void ShaderProgram::pushAttribute() const
{
    // ugly as fuck !
    // mixing compile-time template compilation with runtime check :/
    // implement a static_for loop ?
    // but probably a bad idea to use template in this case

    for (auto it : this->m_attributeStack) {
        AttributeName attribute = it.first;
        BaseOpenGLAttribut::SPtr value = it.second;

        switch (attribute) {
        case ClearColor:
            PushAndApply<ClearColor>(value);
            break;
        case CullFace:
            PushAndApply<CullFace>(value);
            break;
        case DepthFunc:
            PushAndApply<DepthFunc>(value);
            break;
        case DepthMask:
            PushAndApply<DepthMask>(value);
            break;
        case DepthTest:
            PushAndApply<DepthTest>(value);
            break;
        case Viewport:
            PushAndApply<Viewport>(value);
            break;
        }
    }
}

void ShaderProgram::popAttribute() const
{
    // same as above, ugly idea

    for (auto it : this->m_attributeStack) {
        AttributeName attribute = it.first;

        switch (attribute) {
        case ClearColor:
            OpenGLStateMachine::Pop<ClearColor>();
            break;
        case CullFace:
            OpenGLStateMachine::Pop<CullFace>();
            break;
        case DepthFunc:
            OpenGLStateMachine::Pop<DepthFunc>();
            break;
        case DepthMask:
            OpenGLStateMachine::Pop<DepthMask>();
            break;
        case DepthTest:
            OpenGLStateMachine::Pop<DepthTest>();
            break;
        case Viewport:
            OpenGLStateMachine::Pop<Viewport>();
            break;
        }
    }
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
        glGetProgramInfoLog(m_programId, 512, nullptr, infoLog);
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

void ShaderProgram::bind() const
{
    glUseProgram(m_programId);
    this->pushAttribute();
}

void ShaderProgram::unbind() const
{
    this->popAttribute();
    glUseProgram(0);
}

void ShaderProgram::updateDataIfDirty()
{
    for (auto it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        BaseData* baseData = it->second;
        baseData->updateIfDirty();
    }
}

bool ShaderProgram::addUniformBlock(const char* name, unsigned int binding_index)
{
    unsigned int block_index = glGetUniformBlockIndex(this->m_programId, name);

    if (block_index == GL_INVALID_INDEX) {
        msg_warning("ShaderProgram") << "uniform block location '" << name << "' not found. Binding index not added";
        return false;
    }

    glUniformBlockBinding(this->m_programId, block_index, binding_index);

    return true;
}

int ShaderProgram::attributLocation(const char* name) const
{
    if (!m_isLinked)
        return -1;

    return glGetUniformLocation(this->m_programId, name);
}

void ShaderProgram::setUniformValue(const char* name, float x)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, x);
}

void ShaderProgram::setUniformValue(int attributLocation, float x)
{
    glUniform1f(attributLocation, x);
}

void ShaderProgram::setUniformValue(const char* name, const glm::vec2& v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::vec2& v)
{
    glUniform2fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgram::setUniformValue(const char* name, const glm::vec3& v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::vec3& v)
{
    glUniform3fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgram::setUniformValue(const char *name, const glm::vec4 &v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::vec4& v)
{
    glUniform4fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat2& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::mat2& m)
{
    glUniformMatrix2fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat3& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::mat3& m)
{
    glUniformMatrix3fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat4& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgram::setUniformValue(int attributLocation, const glm::mat4& m)
{
    glUniformMatrix4fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}
