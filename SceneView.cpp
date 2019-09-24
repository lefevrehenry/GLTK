#include "SceneView.h"

#include "Node.h"
#include "Scene.h"
#include "Visitor.h"
#include "VisualManager.h"
#include "OpenGLStateMachine.h"

using namespace gl;

static DrawVisitor defaultVisitor;

SceneView::SceneView(const class Viewport& viewport, CameraType type) :
    m_viewport(viewport),
    m_scene(nullptr),
    m_camera(nullptr),
    m_interface(nullptr)
//    m_drawCallback()
{
    this->setInterface(type);
}

SceneView::SceneView(int x, int y, int width, int height, CameraType type) :
    m_viewport(x,y,width,height),
    m_scene(nullptr),
    m_camera(nullptr),
    m_interface(nullptr)
//    m_drawCallback()
{
    this->setInterface(type);
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

//void SceneView::setDrawCallback(std::function<void()> drawCallback)
//{
//    this->m_drawCallback = drawCallback;
//}

void SceneView::draw() const
{
    OpenGLStateMachine::Push<Viewport>();

    int x = static_cast<int>(m_viewport.x());
    int y = static_cast<int>(m_viewport.y());
    int width = static_cast<int>(m_viewport.rw());
    int height = static_cast<int>(m_viewport.rh());

    glViewport(x,y,width,height);

//    if(m_camera)
//        VisualManager::UpdateUniformBufferCamera(*m_camera);

//    if(this->m_drawCallback)
//        this->m_drawCallback();

    if(this->m_scene) {
        Visitor* visitor = (this->m_visitor ? this->m_visitor.get() : &defaultVisitor);

        Node* node = m_scene->root();
        node->executeVisitor(visitor);
    }

    OpenGLStateMachine::Pop<Viewport>();
}
