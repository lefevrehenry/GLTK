#include "DrawVisitor.h"

#include <Material.h>
#include <Node.h>
#include <ShaderProgram.h>
#include <ShaderProgramPrivate.h>
#include <Transform.h>
#include <VisualModel.h>
#include <VisualManager.h>

using namespace gl;

DrawVisitor::DrawVisitor() :
    m_shaderStack(),
    m_optionStack(),
    m_currentShader(nullptr),
    m_currentOption(nullptr)
{

}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::start()
{
    this->m_currentShader = nullptr;
    this->m_currentOption = nullptr;
}

void DrawVisitor::forwardNode(const Node* node)
{
    ShaderProgram* shaderProgram = node->shaderProgram();

    // stack the node's ShaderProgram
    if (shaderProgram != nullptr)
        m_shaderStack.push(shaderProgram);

    // get the current shader program
    if (!m_shaderStack.empty())
        m_currentShader = m_shaderStack.top();

//    // stack the node's VisualOption
//    VisualOption* visualOption = node->visualOption();
//    if (visualOption != nullptr)
//        m_optionStack.push(visualOption);

//    VisualOption* m_currentOption = nullptr;

//    // get the current visual option
//    if (!m_optionStack.empty()) {
//        m_currentOption = m_optionStack.top();
//        m_currentOption->push();
//    }
}

void DrawVisitor::processNode(const Node* node)
{
    if (m_currentShader != nullptr) {
        // bind the current ShaderProgram
        m_currentShader->bind();
        m_currentShader->updateDataIfDirty();

        // fetch the number of instance rendering
        // fetch what kind of primitives has to be drawn by the shader

        VisualParam param = VisualParam::DefaultInstance();
//        param.nbInstance = m_currentShader->getNbInstance();
//        param.primitiveType = m_currentShader->getPrimitiveType();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            VisualModel::CSPtr visualModel(node->getVisual(i));
            const Transform& transform = visualModel->transform();
            const Material& material = visualModel->material();

            VisualManager::UpdateUniformBufferTransform(transform);
            VisualManager::UpdateUniformBufferMaterial(material);

            visualModel->draw(&param);
        }

        // unbind the current ShaderProgram
        m_currentShader->unbind();
    }
}

void DrawVisitor::backwardNode(const Node* node)
{
    ShaderProgram* shaderProgram = node->shaderProgram();

    // unstack the node's ShaderProgram
    if (shaderProgram != nullptr)
        m_shaderStack.pop();

//    // pop the current visual option
//    if (m_currentOption != nullptr)
//        m_currentOption->pop();

//    // unstack the node's visualOption
//    if (visualOption != nullptr)
//        m_optionStack.pop();
}
