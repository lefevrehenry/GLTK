#include "ShaderProgramPrivate.h"

#include <FileRepository.h>
#include <Message.h>
#include <SceneGraph.h>
#include <Shader.h>
#include <VisualManager.h>

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

ShaderProgramPrivate* ShaderProgramPrivate::Create(ShaderProgramType shaderProgramType)
{
    typedef Shader::ShaderType ShaderType;

    ShaderProgramPrivate* shaderProgramPrivate = new ShaderProgramPrivate();

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
        shaderProgramPrivate->addShader(vertexShader);
    }

    if (gs != "") {
        geometryShader.compileSourceCode(gs);
        shaderProgramPrivate->addShader(geometryShader);
    }

    if (fs != "") {
        fragmentShader.compileSourceCode(fs);
        shaderProgramPrivate->addShader(fragmentShader);
    }

    shaderProgramPrivate->link();

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Normal:

        shaderProgramPrivate->addData<float>("scale", 0.5f);
        shaderProgramPrivate->addData<glm::vec3>("normalColor", glm::vec3(1,1,1));
        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::FlatShading:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::GouraudShading:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::PhongShading:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Frame:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);
        shaderProgramPrivate->setNbInstance(3);

        break;
    case ShaderProgramType::HighLight:

        shaderProgramPrivate->addData<glm::vec3>("color", glm::vec3(1.0,0.8,0.0));
        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->set<DepthFunc>(GL_LEQUAL);
        shaderProgramPrivate->set<LineWidth>(2.0f);
        shaderProgramPrivate->set<PolygonMode>(GL_LINE);

        break;
    case ShaderProgramType::BasicTexturing:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Texturing:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::TangentSpace:

//        shaderProgramPrivate->setPrimitiveType(PrimitiveType::POINTS);
        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->setUniformValue("scale", .5);

        break;
    case ShaderProgramType::Picking:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::OutLine:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::MatCap:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::VaoQuad:

        break;
    case ShaderProgramType::Deferred:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::ShadowMapping:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::NormalMapping:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::CubeMap:

        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgramPrivate->set<CullFace>(GL_FALSE);
        shaderProgramPrivate->set<DepthFunc>(GL_LEQUAL);

        break;
    case ShaderProgramType::EnvironmentMapping:

        shaderProgramPrivate->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgramPrivate->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    }

    return shaderProgramPrivate;
}

ShaderProgramPrivate::ShaderProgramPrivate() :
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

ShaderProgramPrivate::~ShaderProgramPrivate()
{
    for (auto it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        BaseData* baseData = it->second;
        delete baseData;
        baseData = nullptr;
    }
    glDeleteProgram(m_programId);
}

GLuint ShaderProgramPrivate::getProgramID() const
{
    return this->m_programId;
}

void ShaderProgramPrivate::link()
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

bool ShaderProgramPrivate::isLinked() const
{
    return m_isLinked;
}

unsigned int ShaderProgramPrivate::getNbInstance() const
{
    return this->m_nbInstance;
}

void ShaderProgramPrivate::setNbInstance(unsigned int n)
{
    this->m_nbInstance = n;
}

PrimitiveType ShaderProgramPrivate::getPrimitiveType() const
{
    return this->m_primitiveType;
}

void ShaderProgramPrivate::setPrimitiveType(PrimitiveType primitiveType)
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

void ShaderProgramPrivate::pushAttribute() const
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
        case LineWidth:
            PushAndApply<LineWidth>(value);
            break;
        case PolygonMode:
            PushAndApply<PolygonMode>(value);
            break;
        case SceneLight:
            PushAndApply<SceneLight>(value);
            break;
        case Viewport:
            PushAndApply<Viewport>(value);
            break;
        }
    }
}

void ShaderProgramPrivate::popAttribute() const
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
        case LineWidth:
            OpenGLStateMachine::Pop<LineWidth>();
            break;
        case PolygonMode:
            OpenGLStateMachine::Pop<PolygonMode>();
            break;
        case SceneLight:
            OpenGLStateMachine::Pop<SceneLight>();
            break;
        case Viewport:
            OpenGLStateMachine::Pop<Viewport>();
            break;
        }
    }
}

bool ShaderProgramPrivate::addShader(const Shader& shader)
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

void ShaderProgramPrivate::bind() const
{
    glUseProgram(m_programId);
    this->pushAttribute();
}

void ShaderProgramPrivate::unbind() const
{
    this->popAttribute();
    glUseProgram(0);
}

void ShaderProgramPrivate::updateDataIfDirty()
{
    for (auto it = m_dataList.begin(); it != m_dataList.end(); ++it) {
        BaseData* baseData = it->second;
        baseData->updateIfDirty();
    }
}

bool ShaderProgramPrivate::addUniformBlock(const char* name, unsigned int binding_index)
{
    unsigned int block_index = glGetUniformBlockIndex(this->m_programId, name);

    if (block_index == GL_INVALID_INDEX) {
        msg_warning("ShaderProgram") << "uniform block location '" << name << "' not found. Binding index not added";
        return false;
    }

    glUniformBlockBinding(this->m_programId, block_index, binding_index);

    return true;
}

int ShaderProgramPrivate::attributLocation(const char* name) const
{
    if (!m_isLinked)
        return -1;

    return glGetUniformLocation(this->m_programId, name);
}

void ShaderProgramPrivate::setUniformValue(const char* name, float x)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, x);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, float x)
{
    glUniform1f(attributLocation, x);
}

void ShaderProgramPrivate::setUniformValue(const char* name, const glm::vec2& v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::vec2& v)
{
    glUniform2fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgramPrivate::setUniformValue(const char* name, const glm::vec3& v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::vec3& v)
{
    glUniform3fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgramPrivate::setUniformValue(const char *name, const glm::vec4 &v)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, v);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::vec4& v)
{
    glUniform4fv(attributLocation, 1, glm::value_ptr(v));
}

void ShaderProgramPrivate::setUniformValue(const char* name, const glm::mat2& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::mat2& m)
{
    glUniformMatrix2fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgramPrivate::setUniformValue(const char* name, const glm::mat3& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::mat3& m)
{
    glUniformMatrix3fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgramPrivate::setUniformValue(const char* name, const glm::mat4& m)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, m);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, const glm::mat4& m)
{
    glUniformMatrix4fv(attributLocation, 1, GL_FALSE, glm::value_ptr(m));
}
