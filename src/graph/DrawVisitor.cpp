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
    m_currentShader(nullptr)
{

}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::start()
{
    this->m_currentShader = nullptr;
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
}

void DrawVisitor::processNode(const Node* node)
{
    if (m_currentShader != nullptr) {
        // bind the current ShaderProgram
        m_currentShader->bind();
//        m_currentShader->updateDataIfDirty();

        // get VisualParam for
//        ShaderProgramPrivate* shaderProgramPrivate = m_currentShader->shaderProgramPrivate();
//        VisualParam param = shaderProgramPrivate->visualParam();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            VisualModel::CSPtr visualModel(node->getVisual(i));
            const Transform& transform = visualModel->transform();
            const Material& material = visualModel->material();

            VisualManager::UpdateUniformBufferTransform(transform);
            VisualManager::UpdateUniformBufferMaterial(material);

            visualModel->draw(/*&param*/);
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
}
