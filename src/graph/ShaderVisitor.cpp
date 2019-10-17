#include "ShaderVisitor.h"

#include <ShaderProgram.h>

using namespace gl;

using ShaderProgramType = GLTK::ShaderProgramType;

ShaderVisitor::ShaderVisitor() :
    m_shaderProgram(nullptr)
{

}

ShaderVisitor::ShaderVisitor(ShaderProgram* shaderProgram) :
    m_shaderProgram(nullptr)
{
    this->setShaderProgram(shaderProgram);
}

ShaderProgram* ShaderVisitor::shaderProgram() const
{
    return this->m_shaderProgram.get();
}

void ShaderVisitor::setShaderProgram(ShaderProgram* shaderProgram)
{
    this->m_shaderProgram.reset(shaderProgram);
}

void ShaderVisitor::processNode(const Node* node)
{
    ShaderProgram* oldShaderProgram = m_currentShader;
    m_currentShader = this->m_shaderProgram.get();

    DrawVisitor::processNode(node);

    m_currentShader = oldShaderProgram;
}
