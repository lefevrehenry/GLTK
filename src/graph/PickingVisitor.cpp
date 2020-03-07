#include "PickingVisitor.h"

#include <BaseApplication.h>
#include <Framebuffer.h>
#include <Node.h>
#include <OpenGLStateMachine.h>
#include <ShaderProgramPrivate.h>
#include <Transform.h>
#include <VisualManager.h>
#include <VisualModel.h>

// Glad
#include <glad/glad.h>

using namespace gl;

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
    m_selectedVisualModel(),
    m_selectedPosition(),
    m_x(0),
    m_y(0),
    m_id(0)
{
    unsigned int width = BaseApplication::ScreenWidth;
    unsigned int height = BaseApplication::ScreenHeight;

    this->m_pickingFramebuffer.reset(new Framebuffer(width, height));
    this->m_pickingFramebuffer->attachTexture();
    this->m_pickingFramebuffer->attachDepthTexture();

//    this->m_shaderProgram.reset(ShaderProgramPrivate::Create(GLTK::ShaderProgramType::Picking));
}

void PickingVisitor::set(int x, int y)
{
    this->m_x = x;
    this->m_y = y;
}

std::weak_ptr<const VisualModel> PickingVisitor::selectedVisualModel() const
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
//    this->m_shaderProgram->updateDataIfDirty();

    this->m_visualModels.clear();
    this->m_visualModels.push_back(VisualModel::CWPtr());

    this->m_selectedVisualModel = VisualModel::CWPtr();
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
        VisualModel::CWPtr visualModel = this->m_visualModels[index];

        float z = 1.0;
        glReadPixels(this->m_x, this->m_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

        float w = BaseApplication::ScreenWidth;
        float h = BaseApplication::ScreenHeight;

        float ndc_x = (this->m_x / w) * 2.f - 1;
        float ndc_y = (this->m_y / h) * 2.f - 1;
        float ndc_z = (z * 2.f) - 1;

        this->m_selectedVisualModel = visualModel;
        this->m_selectedPosition = glm::vec3(ndc_x,ndc_y,ndc_z);
    }

    this->m_pickingFramebuffer->unbind();
    this->m_shaderProgram->unbind();
}

void PickingVisitor::processNode(const Node* node)
{
//    VisualParam param = VisualParam::DefaultInstance();

    // draw each mesh
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        VisualModel::CSPtr visualModel = node->getVisual(i);
        const Transform& transform = visualModel->transform();

        VisualManager::UpdateUniformBufferTransform(transform);

        this->m_shaderProgram->setUniformValue("index", packIndex(this->m_id));
        this->m_visualModels.push_back(visualModel);

        visualModel->draw(/*&param*/);

        this->m_id += 1;
    }
}
