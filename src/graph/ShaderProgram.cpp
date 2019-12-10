#include "ShaderProgram.h"

#include <CubeMapTexturePrivate.h>
#include <ShaderProgramPrivate.h>
#include <TexturePrivate2D.h>
#include <VisualManager.h>

using namespace gl;

ShaderProgram::ShaderProgram() :
    m_shaderProgramPrivate(new ShaderProgramPrivate())
{

}

std::string ShaderProgram::vertexShaderCode() const
{
    return this->m_vertexShaderCode;
}

void ShaderProgram::setVertexShaderCode(const std::string& vertexShaderCode)
{
    this->m_vertexShaderCode = vertexShaderCode;
}

std::string ShaderProgram::geometryShaderCode() const
{
    return this->m_geometryShaderCode;
}

void ShaderProgram::setGeometryShaderCode(const std::string& geometryShaderCode)
{
    this->m_geometryShaderCode = geometryShaderCode;
}

std::string ShaderProgram::fragmentShaderCode() const
{
    return this->m_fragmentShaderCode;
}

void ShaderProgram::setFragmentShaderCode(const std::string& fragmentShaderCode)
{
    this->m_fragmentShaderCode = fragmentShaderCode;
}

void ShaderProgram::link()
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->link(m_vertexShaderCode, m_geometryShaderCode, m_fragmentShaderCode);
}

bool ShaderProgram::isLinked() const
{
    if(this->m_shaderProgramPrivate == nullptr)
        return false;

    return this->m_shaderProgramPrivate->isLinked();
}

void ShaderProgram::attachUniformBufferTransform(const char* name)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->attachUniformBlock(name, VisualManager::TransformIndex);
}

void ShaderProgram::attachUniformBufferMaterial(const char* name)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->attachUniformBlock(name, VisualManager::MaterialIndex);
}

void ShaderProgram::attachUniformBufferCamera(const char* name)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->attachUniformBlock(name, VisualManager::CameraIndex);
}

void ShaderProgram::attachUniformBufferLight(const char* name)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->attachUniformBlock(name, VisualManager::LightIndex);
}

void ShaderProgram::attachUniformBufferTime(const char* name)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->attachUniformBlock(name, VisualManager::TimeIndex);
}

void ShaderProgram::setUniformValue(const char* name, float x)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, x);
}

void ShaderProgram::setUniformValue(const char* name, const glm::vec2& v)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, v);
}

void ShaderProgram::setUniformValue(const char* name, const glm::vec3& v)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, v);
}

void ShaderProgram::setUniformValue(const char* name, const glm::vec4& v)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, v);
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat2& m)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, m);
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat3& m)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, m);
}

void ShaderProgram::setUniformValue(const char* name, const glm::mat4& m)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->setUniformValue(name, m);
}

void ShaderProgram::setUniformValue(const char* name, Texture2D::SPtr t)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    TexturePrivate2D::SPtr texturePrivate = std::static_pointer_cast<TexturePrivate2D>(t->texturePrivate());
    this->m_shaderProgramPrivate->setUniformValue(name, texturePrivate);
}

void ShaderProgram::setUniformValue(const char* name, CubeMapTexture::SPtr t)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    CubeMapTexturePrivate::SPtr texturePrivate = std::static_pointer_cast<CubeMapTexturePrivate>(t->texturePrivate());
    this->m_shaderProgramPrivate->setUniformValue(name, texturePrivate);
}

void ShaderProgram::bind() const
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->bind();
}

void ShaderProgram::unbind() const
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->unbind();
}

std::shared_ptr<ShaderProgramPrivate> ShaderProgram::shaderProgramPrivate() const
{
    return this->m_shaderProgramPrivate;
}
