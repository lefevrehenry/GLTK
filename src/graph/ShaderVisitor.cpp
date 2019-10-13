#include "ShaderVisitor.h"

#include <opengl/ShaderProgram.h>

using namespace gl;

using ShaderProgramType = GLTK::ShaderProgramType;

ShaderVisitor::ShaderVisitor() :
    m_shaderProgram(nullptr)
{

}

ShaderVisitor::ShaderVisitor(ShaderProgramType shaderProgramType) :
    m_shaderProgram(nullptr)
{
    this->setShaderProgram(shaderProgramType);
}

void ShaderVisitor::setShaderProgram(ShaderProgramType shaderProgramType)
{
    this->m_shaderProgram.reset(ShaderProgramPrivate::Create(shaderProgramType));
}

void ShaderVisitor::processNode(const Node* node)
{
    ShaderProgramPrivate* oldShaderProgram = m_currentShader;
    m_currentShader = this->m_shaderProgram.get();

    DrawVisitor::processNode(node);

    m_currentShader = oldShaderProgram;
}
