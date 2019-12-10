#include "DrawWithSelectionVisitor.h"

#include <Node.h>
#include <ShaderProgramPrivate.h>
#include <VisualModel.h>
#include <VisualManager.h>

using namespace gl;

DrawVisitorWithSelection::DrawVisitorWithSelection() : DrawVisitor(),
    m_outlineShader(nullptr),
    m_selected(nullptr)
{
//    this->m_outlineShader.reset(ShaderProgramPrivate::Create(GLTK::ShaderProgramType::OutLine));
}

void DrawVisitorWithSelection::start()
{
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    DrawVisitor::start();
}

void DrawVisitorWithSelection::forwardNode(const Node* node)
{
    if (this->m_selected != nullptr) {

//        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            VisualModel::CSPtr visualModel(node->getVisual(i));

            if (visualModel == this->m_selected) {
                m_outlineShader->bind();
//                m_outlineShader->updateDataIfDirty();

                // draw the object with filled primitives
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                // activate stencil buffer test
                glEnable(GL_STENCIL_TEST);
                // deactivate depth buffer test
                glDisable(GL_DEPTH_TEST);
                // set the stencil buffer to write a 1 in every time a pixel is written to the screen
                glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
                // disable color buffer
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

                const Transform& transform = visualModel->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visualModel->draw(/*&param*/);

                // enable color buffer
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                // activate depth buffer test
                glEnable(GL_DEPTH_TEST);
                // deactivate stencil buffer test
                glDisable(GL_STENCIL_TEST);

                m_outlineShader->unbind();
            }
        }
    }

    DrawVisitor::forwardNode(node);
}

void DrawVisitorWithSelection::backwardNode(const Node* node)
{
    if (this->m_selected != nullptr) {

//        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            VisualModel::CSPtr visualModel(node->getVisual(i));

            if (visualModel == this->m_selected) {
                m_outlineShader->bind();
//                m_outlineShader->updateDataIfDirty();

                // draw the object with thick lines
                glLineWidth(3.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                // activate stencil buffer test
                glEnable(GL_STENCIL_TEST);
                // set the stencil buffer to only allow writing
                // to the screen when the value of the
                // stencil buffer is not 1
                glStencilFunc(GL_NOTEQUAL, 1, 0xFFFFFFFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

                const Transform& transform = visualModel->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visualModel->draw(/*&param*/);

                // deactivate stencil buffer test
                glDisable(GL_STENCIL_TEST);

                glLineWidth(1.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                m_outlineShader->unbind();
            }
        }
    }

    DrawVisitor::backwardNode(node);
}
