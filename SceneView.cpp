#include "SceneView.h"

#include "Node.h"
#include "SceneGraph.h"
#include "Visitor.h"
#include "VisualManager.h"
#include "OpenGLStateMachine.h"

using namespace gl;

static DrawVisitor defaultVisitor;

SceneView::SceneView() :
    m_viewport(),
    m_backgroundcolor(0.2f,0.2f,0.2f,1.0f),
    m_scene(),
    m_camera(new Camera()),
    m_interface(nullptr)
{
}

const class Viewport& SceneView::viewport() const
{
    return this->m_viewport;
}

void SceneView::setViewport(const class Viewport& viewport)
{
    this->m_viewport = viewport;
}

glm::vec4 SceneView::backgroundColor() const
{
    return this->m_backgroundcolor;
}

void SceneView::setBackgroundColor(const glm::vec4& backgroundColor)
{
    this->m_backgroundcolor = backgroundColor;
}

SceneGraph* SceneView::scene() const
{
    std::shared_ptr<SceneGraph> scene(this->m_scene);

    return scene.get();
}

void SceneView::setScene(std::weak_ptr<SceneGraph> scene)
{
    this->m_scene = std::shared_ptr<SceneGraph>(scene);
}

Camera* SceneView::camera() const
{
    std::shared_ptr<Camera> camera(this->m_camera);

    return camera.get();
}

void SceneView::setCamera(std::weak_ptr<Camera> camera)
{
    this->m_camera = std::shared_ptr<Camera>(camera);
}

const std::shared_ptr<Controller>& SceneView::interface() const
{
    return this->m_interface;
}

void SceneView::setInterface(const std::shared_ptr<Controller>& interface)
{
    this->m_interface = interface;
}

void SceneView::draw() const
{
    OpenGLStateMachine::Push<Viewport>();
    OpenGLStateMachine::Push<ClearColor>();

    int x = m_viewport.x();
    int y = m_viewport.y();
    int width = m_viewport.width();
    int height = m_viewport.height();

    glViewport(x,y,width,height);

    float r = m_backgroundcolor.r;
    float g = m_backgroundcolor.g;
    float b = m_backgroundcolor.b;
    float a = m_backgroundcolor.a;

    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(this->m_camera)
        VisualManager::UpdateUniformBufferCamera(*m_camera);

    std::shared_ptr<SceneGraph> scene(this->m_scene);
    if(scene) {
        Visitor* visitor = (this->m_visitor ? this->m_visitor.get() : &defaultVisitor);

        Node* node = scene->root();
        node->executeVisitor(visitor);
    }

    OpenGLStateMachine::Pop<ClearColor>();
    OpenGLStateMachine::Pop<Viewport>();
}