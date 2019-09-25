#include "SceneView.h"

#include "Node.h"
#include "SceneGraph.h"
#include "Visitor.h"
#include "VisualManager.h"
#include "OpenGLStateMachine.h"

using namespace gl;

static DrawVisitor defaultVisitor;

SceneView::SceneView(const class Viewport& viewport) :
    m_viewport(viewport),
    m_scene(),
    m_camera(new Camera()),
    m_interface(nullptr)
{
}

SceneView::SceneView(int x, int y, int width, int height) :
    m_viewport(x,y,width,height),
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

std::weak_ptr<SceneGraph> SceneView::scene() const
{
    return this->m_scene;
}

void SceneView::setScene(std::weak_ptr<SceneGraph> scene)
{
    this->m_scene = std::shared_ptr<SceneGraph>(scene);
}

std::weak_ptr<Camera> SceneView::camera() const
{
    return this->m_camera;
}

void SceneView::setCamera(std::weak_ptr<Camera> camera)
{
    this->m_camera = std::shared_ptr<Camera>(camera);
}

const std::unique_ptr<Interface>& SceneView::interface() const
{
    return this->m_interface;
}

void SceneView::setInterface(CameraType type)
{
    this->m_interface.reset(CameraController::Create(type, camera()));
}

void SceneView::draw() const
{
    OpenGLStateMachine::Push<Viewport>();

    int x = static_cast<int>(m_viewport.x());
    int y = static_cast<int>(m_viewport.y());
    int width = static_cast<int>(m_viewport.rw());
    int height = static_cast<int>(m_viewport.rh());

    glViewport(x,y,width,height);

    if(this->m_camera)
        VisualManager::UpdateUniformBufferCamera(*m_camera);

    std::shared_ptr<SceneGraph> scene(this->m_scene);
    if(scene) {
        Visitor* visitor = (this->m_visitor ? this->m_visitor.get() : &defaultVisitor);

        Node* node = scene->root();
        node->executeVisitor(visitor);
    }

    OpenGLStateMachine::Pop<Viewport>();
}
