#include "ShaderProgram.h"

#include <gltk.h>
#include <opengl/ShaderProgramPrivate.h>

using namespace gl;

ShaderProgram* ShaderProgram::Create(GLTK::ShaderProgramType shaderProgramType)
{
    ShaderProgramPrivate* shaderProgramPrivate = ShaderProgramPrivate::Create(shaderProgramType);
    ShaderProgram* shaderProgram = new ShaderProgram(shaderProgramPrivate);

    return shaderProgram;
}

ShaderProgram::ShaderProgram() :
    m_shaderProgramPrivate()
{

}

ShaderProgram::ShaderProgram(ShaderProgramPrivate* shaderProgramPrivate) :
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
