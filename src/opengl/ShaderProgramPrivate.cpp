#include "ShaderProgramPrivate.h"

#include <Message.h>
#include <Shader.h>

// Glad
#include <glad/glad.h>

// Glm
#include <glm/gtc/type_ptr.hpp>

using namespace gl;

//ShaderProgramPrivate* ShaderProgramPrivate::Create(ShaderProgramType shaderProgramType)
//{
//    typedef Shader::ShaderType ShaderType;

//    ShaderProgramPrivate* shaderProgramPrivate = new ShaderProgramPrivate();

//    std::string vertexFilename = "";
//    std::string geometryFilename = "";
//    std::string fragmentFilename = "";

//    std::string vs = "";
//    std::string gs = "";
//    std::string fs = "";

//    Shader vertexShader(ShaderType::Vertex);
//    Shader geometryShader(ShaderType::Geometry);
//    Shader fragmentShader(ShaderType::Fragment);

//    switch (shaderProgramType)
//    {
//    case ShaderProgramType::Basic:

//        vertexFilename = "shaders/basic.vs";
//        fragmentFilename = "shaders/basic.fs";

//        break;
//    case ShaderProgramType::Normal:

//        vertexFilename = "shaders/normal.vs";
//        geometryFilename = "shaders/normal.gs";
//        fragmentFilename = "shaders/normal.fs";

//        break;
//    case ShaderProgramType::FlatShading:

//        vertexFilename = "shaders/flatShading.vs";
//        geometryFilename = "shaders/flatShading.gs";
//        fragmentFilename = "shaders/flatShading.fs";

//        break;
//    case ShaderProgramType::GouraudShading:

//        vertexFilename = "shaders/gouraudShading.vs";
//        fragmentFilename = "shaders/gouraudShading.fs";

//        break;
//    case ShaderProgramType::PhongShading:

//        vertexFilename = "shaders/phongShading.vs";
//        fragmentFilename = "shaders/phongShading.fs";

//        break;

//    case ShaderProgramType::Frame:

//        vertexFilename = "shaders/frame.vs";
//        fragmentFilename = "shaders/frame.fs";

//        break;
//    case ShaderProgramType::HighLight:

//        vertexFilename = "shaders/highLight.vs";
//        geometryFilename = "shaders/highLight.gs";
//        fragmentFilename = "shaders/highLight.fs";

//        break;
//    case ShaderProgramType::BasicTexturing:

//        vertexFilename = "shaders/basicTexturing.vs";
//        fragmentFilename = "shaders/basicTexturing.fs";

//        break;
//    case ShaderProgramType::Texturing:

//        vertexFilename = "shaders/texturing.vs";
//        fragmentFilename = "shaders/texturing.fs";

//        break;
//    case ShaderProgramType::TangentSpace:

//        vertexFilename = "shaders/tangentSpace.vs";
//        geometryFilename = "shaders/tangentSpace.gs";
//        fragmentFilename = "shaders/tangentSpace.fs";

//        break;
//    case ShaderProgramType::Picking:

//        vertexFilename = "shaders/picking.vs";
//        fragmentFilename = "shaders/picking.fs";

//        break;
//    case ShaderProgramType::OutLine:

//        vertexFilename = "shaders/outline.vs";
//        fragmentFilename = "shaders/outline.fs";

//        break;
//    case ShaderProgramType::MatCap:

//        vertexFilename = "shaders/matcap.vs";
//        fragmentFilename = "shaders/matcap.fs";

//        break;
//    case ShaderProgramType::VaoQuad:

//        vertexFilename = "shaders/vaoQuad.vs";
//        fragmentFilename = "shaders/vaoQuad.fs";

//        break;
//    case ShaderProgramType::Deferred:

//        vertexFilename = "shaders/deferred.vs";
//        fragmentFilename = "shaders/deferred.fs";

//        break;
//    case ShaderProgramType::ShadowMapping:

//        vertexFilename = "shaders/shadowMapping.vs";
//        fragmentFilename = "shaders/shadowMapping.fs";

//        break;
//    case ShaderProgramType::NormalMapping:

//        vertexFilename = "shaders/normalMapping.vs";
//        fragmentFilename = "shaders/normalMapping.fs";

//        break;
//    case ShaderProgramType::CubeMap:

//        vertexFilename = "shaders/cubeMap.vs";
//        fragmentFilename = "shaders/cubeMap.fs";

//        break;
//    case ShaderProgramType::EnvironmentMapping:

//        vertexFilename = "shaders/environmentMapping.vs";
//        fragmentFilename = "shaders/environmentMapping.fs";

//        break;
//    case ShaderProgramType::DisplacementMapping:

//        vertexFilename = "shaders/displacementMapping.vs";
//        fragmentFilename = "shaders/displacementMapping.fs";

//        break;
//    }

//    if (DataRepository.findFile(vertexFilename))
//        getStringFromFile(vertexFilename, vs);

//    if (DataRepository.findFile(geometryFilename))
//        getStringFromFile(geometryFilename, gs);

//    if (DataRepository.findFile(fragmentFilename))
//        getStringFromFile(fragmentFilename, fs);

//    if (vs != "") {
//        vertexShader.compileSourceCode(vs);
//        shaderProgramPrivate->addShader(vertexShader);
//    }

//    if (gs != "") {
//        geometryShader.compileSourceCode(gs);
//        shaderProgramPrivate->addShader(geometryShader);
//    }

//    if (fs != "") {
//        fragmentShader.compileSourceCode(fs);
//        shaderProgramPrivate->addShader(fragmentShader);
//    }

//    shaderProgramPrivate->link();

//    switch (shaderProgramType)
//    {
//    case ShaderProgramType::Basic:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::Normal:

//        shaderProgramPrivate->setUniformValue("scale", .5f);
//        shaderProgramPrivate->setUniformValue("normalColor", glm::vec3(1,1,1));
//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::FlatShading:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::GouraudShading:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::PhongShading:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::Frame:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);
////        shaderProgramPrivate->setInstancing(3);

//        break;
//    case ShaderProgramType::HighLight:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->setUniformValue("color", glm::vec3(1.0,0.8,0.0));
//        shaderProgramPrivate->setRenderState<DepthFunc>(GL_LEQUAL);
//        shaderProgramPrivate->setRenderState<LineWidth>(2.0f);
//        shaderProgramPrivate->setRenderState<PolygonMode>(GL_LINE);

//        break;
//    case ShaderProgramType::BasicTexturing:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::Texturing:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::TangentSpace:

////        shaderProgramPrivate->setPrimitiveType(VisualParam::PrimitiveType::POINTS);
//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->setUniformValue("scale", .5);

//        break;
//    case ShaderProgramType::Picking:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::OutLine:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::MatCap:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::VaoQuad:

//        break;
//    case ShaderProgramType::Deferred:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::ShadowMapping:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::NormalMapping:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("material", VisualManager::MaterialIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    case ShaderProgramType::CubeMap:

//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->setRenderState<CullFace>(GL_FALSE);
//        shaderProgramPrivate->setRenderState<DepthFunc>(GL_LEQUAL);

//        break;
//    case ShaderProgramType::EnvironmentMapping:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);

//        break;
//    case ShaderProgramType::DisplacementMapping:

//        shaderProgramPrivate->attachUniformBlock("transform", VisualManager::TransformIndex);
//        shaderProgramPrivate->attachUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgramPrivate->attachUniformBlock("light", VisualManager::LightIndex);

//        break;
//    }

//    return shaderProgramPrivate;
//}

ShaderProgramPrivate::ShaderProgramPrivate() :
    m_programId(0),
    m_isLinked(false),
    m_renderState()
{
    m_programId = glCreateProgram();
}

ShaderProgramPrivate::~ShaderProgramPrivate()
{
    glDeleteProgram(m_programId);
}

GLuint ShaderProgramPrivate::getProgramID() const
{
    return m_programId;
}

void ShaderProgramPrivate::link(const std::string& vs, const std::string& gs, const std::string& fs)
{
    typedef Shader::ShaderType ShaderType;

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    if(vs != "")
        vertexShader.compileSourceCode(vs);

    if(gs != "")
        geometryShader.compileSourceCode(gs);

    if(fs != "")
        fragmentShader.compileSourceCode(fs);

    GLint linked = 0;
    Shader* shaders[3] = {&vertexShader, &geometryShader, &fragmentShader};

    for (Shader* shader : shaders) {
        if(shader->isCompiled()) {
            glAttachShader(m_programId, shader->getShaderID());
        }
    }

    glLinkProgram(m_programId);

    glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_programId, 512, nullptr, infoLog);
        msg_error("ShaderProgramPrivate") << "Linkage failed: " << infoLog;
    }

    m_isLinked = linked;

    for (Shader* shader : shaders) {
        glDetachShader(m_programId, shader->getShaderID());
    }
}

bool ShaderProgramPrivate::isLinked() const
{
    return m_isLinked;
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

bool ShaderProgramPrivate::attachUniformBlock(const char* name, unsigned int binding_index)
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

void ShaderProgramPrivate::setUniformValue(const char* name, int x)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, x);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, int x)
{
    glUniform1i(attributLocation, x);
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

void ShaderProgramPrivate::setUniformValue(const char* name, TexturePrivate::SPtr t)
{
    int location = attributLocation(name);

    if (location == -1) {
        msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Uniform value not setted";
        return;
    }

    setUniformValue(location, t);
}

void ShaderProgramPrivate::setUniformValue(int attributLocation, TexturePrivate::SPtr t)
{
    unsigned short unit = t->getTextureUnit();

    t->bind();

    glUniform1i(attributLocation, unit);
}

void ShaderProgramPrivate::pushAttribute() const
{
    this->m_renderState.pushAttribute();
}

void ShaderProgramPrivate::popAttribute() const
{
    this->m_renderState.popAttribute();
}
