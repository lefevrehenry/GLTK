#include "Visitor.h"

#include "Framebuffer.h"
#include "GLFWApplication.h"
#include "Helper.h"
#include "Mesh.h"
#include "Node.h"
#include "OpenGLStateMachine.h"
#include "Selectable.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "VisualManager.h"
#include "VisualModel.h"
#include "VisualOption.h"

using namespace gl;

Visitor::~Visitor()
{

}

void Visitor::start()
{

}

void Visitor::end()
{

}

void Visitor::forwardNode(const Node*)
{

}

void Visitor::backwardNode(const Node*)
{

}

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

        VisualParam param;
        param.nbInstance = m_currentShader->getNbInstance();
        param.primitiveMode = m_currentShader->getPrimitiveMode();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);
            const Transform& transform = visual->transform();
            const Material& material = visual->material();

            VisualManager::UpdateUniformBufferTransform(transform);
            VisualManager::UpdateUniformBufferMaterial(material);

            visual->draw(param);
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

DrawVisitorWithSelection::DrawVisitorWithSelection() : DrawVisitor(),
    m_outlineShader(nullptr),
    m_selected(nullptr)
{
    this->m_outlineShader = ShaderProgram::Create(ShaderProgram::OutLine);

//    Selectable* selected = GLFWApplication::Instance()->selected();
//    if (selected != nullptr) {
//        this->m_selected = selected->visualModel();
//    }
}

DrawVisitorWithSelection::~DrawVisitorWithSelection()
{
    delete m_outlineShader;
    m_outlineShader = nullptr;
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

        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);

            if (visual == this->m_selected) {
                m_outlineShader->bind();
                m_outlineShader->updateDataIfDirty();

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

                const Transform& transform = visual->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visual->draw(param);

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

        VisualParam param = VisualParam::DefaultInstance();

        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);

            if (visual == this->m_selected) {
                m_outlineShader->bind();
                m_outlineShader->updateDataIfDirty();

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

                const Transform& transform = visual->transform();
                VisualManager::UpdateUniformBufferTransform(transform);

                visual->draw(param);

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

glm::vec4 packIndex(unsigned int n)
{
    float r = ((n & 0x000000FF) >>  0) / 255.0f;
    float g = ((n & 0x0000FF00) >>  8) / 255.0f;
    float b = ((n & 0x00FF0000) >> 16) / 255.0f;
    float a = ((n & 0xFF000000) >> 24) / 255.0f;

    return glm::vec4(r,g,b,a);
}

unsigned int unpackIndex(const glm::vec4& color)
{
    unsigned int r = uint(color.r * 255);
    unsigned int g = uint(color.g * 255);
    unsigned int b = uint(color.b * 255);
    unsigned int a = uint(color.a * 255);

    return (a << 24 | b << 16 | g << 8 | r);
}

PickingVisitor::PickingVisitor() :
    m_pickingFramebuffer(nullptr),
    m_shaderProgram(nullptr),
    m_visualModels(0),
    m_selectedVisualModel(nullptr),
    m_selectedPosition(),
    m_x(0),
    m_y(0),
    m_id(0)
{
    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;

    this->m_pickingFramebuffer = new Framebuffer(width, height);
    this->m_pickingFramebuffer->attachTexture();
    this->m_pickingFramebuffer->attachDepthTexture();

    this->m_shaderProgram = ShaderProgram::Create(ShaderProgram::Picking);
}

PickingVisitor::~PickingVisitor()
{
    delete m_pickingFramebuffer;
    m_pickingFramebuffer = nullptr;

    delete m_shaderProgram;
    m_shaderProgram = nullptr;
}

void PickingVisitor::set(int x, int y)
{
    this->m_x = x;
    this->m_y = y;
}

const VisualModel* PickingVisitor::selectedVisualModel() const
{
    return this->m_selectedVisualModel;
}

glm::vec3 PickingVisitor::selectedPosition() const
{
    return this->m_selectedPosition;
}

void PickingVisitor::start()
{
    this->m_pickingFramebuffer->bind();

    OpenGLStateMachine::Push<ClearColor>();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    OpenGLStateMachine::Pop<ClearColor>();

    this->m_shaderProgram->bind();
    this->m_shaderProgram->updateDataIfDirty();

    this->m_visualModels.clear();
    this->m_visualModels.push_back(nullptr);

    this->m_selectedVisualModel = nullptr;
    this->m_selectedPosition = glm::vec3(0,0,0);

    this->m_id = 1;
}

void PickingVisitor::end()
{
    float indexComponents[4];
    glReadPixels(this->m_x, this->m_y, 1, 1, GL_RGBA, GL_FLOAT, &indexComponents[0]);

    glm::vec4 color;
    color.r = indexComponents[0];
    color.g = indexComponents[1];
    color.b = indexComponents[2];
    color.a = indexComponents[3];

    unsigned int index = unpackIndex(color);

    if (index > 0 && index < this->m_visualModels.size()) {
        const VisualModel* visual = this->m_visualModels[index];

        float z = 1.0;
        glReadPixels(this->m_x, this->m_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

        float w = GLFWApplication::ScreenWidth;
        float h = GLFWApplication::ScreenHeight;

        float ndc_x = (this->m_x / w) * 2.f - 1;
        float ndc_y = (this->m_y / h) * 2.f - 1;
        float ndc_z = (z * 2.f) - 1;

        this->m_selectedVisualModel = visual;
        this->m_selectedPosition = glm::vec3(ndc_x,ndc_y,ndc_z);
    }

    this->m_pickingFramebuffer->unbind();
    this->m_shaderProgram->unbind();
}

void PickingVisitor::processNode(const Node* node)
{
    VisualParam param = VisualParam::DefaultInstance();

    // draw each mesh
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        const VisualModel* visual = node->getVisual(i);
        const Transform& transform = visual->transform();

        VisualManager::UpdateUniformBufferTransform(transform);

        this->m_shaderProgram->setUniformValue("index", packIndex(this->m_id));
        this->m_visualModels.push_back(visual);

        visual->draw(param);

        this->m_id += 1;
    }
}

BoundingBoxVisitor::BoundingBoxVisitor()
{

}

BoundingBoxVisitor::~BoundingBoxVisitor()
{

}

void BoundingBoxVisitor::start()
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    this->globalMin = glm::vec3(maxf, maxf, maxf);
    this->globalMax = glm::vec3(minf, minf, minf);
}

void BoundingBoxVisitor::processNode(const Node* node)
{
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        glm::vec3 min;
        glm::vec3 max;

        const VisualModel* visual = node->getVisual(i);
        const Mesh* mesh = visual->mesh();

        if (mesh)
            mesh->getBbox(min, max);

        const Transform& transform = visual->transform();
        min = glm::vec3(transform.matrix() * glm::vec4(min, 1.0));
        max = glm::vec3(transform.matrix() * glm::vec4(max, 1.0));

        // update globalMin
        globalMin[0] = (min[0] < globalMin[0] ? min[0] : globalMin[0]);
        globalMin[1] = (min[1] < globalMin[1] ? min[1] : globalMin[1]);
        globalMin[2] = (min[2] < globalMin[2] ? min[2] : globalMin[2]);
        // update globalMax
        globalMax[0] = (max[0] > globalMax[0] ? max[0] : globalMax[0]);
        globalMax[1] = (max[1] > globalMax[1] ? max[1] : globalMax[1]);
        globalMax[2] = (max[2] > globalMax[2] ? max[2] : globalMax[2]);
    }
}

glm::vec3 BoundingBoxVisitor::getMin() const
{
    return this->globalMin;
}

glm::vec3 BoundingBoxVisitor::getMax() const
{
    return this->globalMax;
}

FetchVisualModelVisitor::FetchVisualModelVisitor() :
    m_visualModels()
{

}

FetchVisualModelVisitor::~FetchVisualModelVisitor()
{

}

void FetchVisualModelVisitor::start()
{
    this->m_visualModels.clear();
}

void FetchVisualModelVisitor::processNode(const Node* node)
{
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        const VisualModel* visual = node->getVisual(i);
        this->m_visualModels.push_front(visual);
    }
}

std::list<const VisualModel*> FetchVisualModelVisitor::getVisualModels() const
{
    return this->m_visualModels;
}

ShaderVisitor::ShaderVisitor() :
    m_shaderProgram(nullptr)
{

}

ShaderVisitor::ShaderVisitor(ShaderProgram* shaderProgram) :
    m_shaderProgram(shaderProgram)
{

}

void ShaderVisitor::setShaderProgram(ShaderProgram* shaderProgram)
{
    this->m_shaderProgram = shaderProgram;
}

void ShaderVisitor::processNode(const Node* node)
{
    ShaderProgram* oldShaderProgram = m_currentShader;
    m_currentShader = this->m_shaderProgram;

    DrawVisitor::processNode(node);

    m_currentShader = oldShaderProgram;
}
