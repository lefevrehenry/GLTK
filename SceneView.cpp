#include "SceneView.h"

#include "Camera.h"
#include "GLFWApplicationEvents.h"
#include "OpenGLStateMachine.h"

using namespace gl;

SceneView::SceneView(const class Viewport& viewport) :
    m_viewport(viewport),
    m_scene(nullptr),
    m_camera(nullptr),
    m_interface(nullptr),
    m_drawCallback()
{

}

SceneView::SceneView(int x, int y, int width, int height) :
    m_viewport(x,y,width,height),
    m_scene(nullptr),
    m_camera(nullptr),
    m_interface(nullptr),
    m_drawCallback()
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

std::weak_ptr<Scene> SceneView::scene() const
{
    return this->m_scene;
}

void SceneView::setScene(std::weak_ptr<Scene> scene)
{
    this->m_scene = std::shared_ptr<Scene>(scene);
}

std::weak_ptr<Camera> SceneView::camera() const
{
    return this->m_camera;
}

void SceneView::setCamera(std::weak_ptr<Camera> camera)
{
    this->m_camera = std::shared_ptr<Camera>(camera);
}

void SceneView::setDrawCallback(std::function<void()> drawCallback)
{
    this->m_drawCallback = drawCallback;
}

void SceneView::draw() const
{
    OpenGLStateMachine::Push<Viewport>();

    int x = static_cast<int>(m_viewport.x());
    int y = static_cast<int>(m_viewport.y());
    int width = static_cast<int>(m_viewport.rw());
    int height = static_cast<int>(m_viewport.rh());

    glViewport(x,y,width,height);

    if(this->m_drawCallback)
        this->m_drawCallback();

    OpenGLStateMachine::Pop<Viewport>();
}
