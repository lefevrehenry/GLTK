#include "ShaderProgram.h"

#include <gltk.h>
#include <ShaderProgramPrivate.h>
#include <Texture.h>

using namespace gl;

ShaderProgram* ShaderProgram::Create(GLTK::ShaderProgramType shaderProgramType)
{
    std::shared_ptr<ShaderProgramPrivate> shaderProgramPrivate( ShaderProgramPrivate::Create(shaderProgramType) );
    ShaderProgram* shaderProgram = new ShaderProgram(shaderProgramPrivate);

    return shaderProgram;
}

ShaderProgram::ShaderProgram() :
    m_shaderProgramPrivate()
{

}

ShaderProgram::ShaderProgram(const std::shared_ptr<ShaderProgramPrivate>& shaderProgramPrivate) :
    m_shaderProgramPrivate(shaderProgramPrivate)
{

}

ShaderProgramPrivate* ShaderProgram::shaderProgramPrivate() const
{
    return this->m_shaderProgramPrivate.get();
}

void ShaderProgram::setShaderProgramPrivate(ShaderProgramPrivate* shaderProgramPrivate)
{
    this->m_shaderProgramPrivate.reset(shaderProgramPrivate);
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

void ShaderProgram::updateDataIfDirty() const
{
    if(this->m_shaderProgramPrivate == nullptr)
        return;

    this->m_shaderProgramPrivate->updateDataIfDirty();
}

bool ShaderProgram::addDataTexture(const char* name, Texture* value)
{
    return addData<Texture>(name, value);
}

bool ShaderProgram::addDataCubeMapTexture(const char* name, CubeMapTexture* value)
{
    return addData<CubeMapTexture>(name, value);
}

template< typename T >
bool ShaderProgram::addData(const char* name, T* value)
{
    if(this->m_shaderProgramPrivate == nullptr)
        return false;

    if(value == nullptr)
        return false;

    return this->m_shaderProgramPrivate->addData<T>(name, *value);
}
