#include "QuickGLFWApplication.h"

#include <GLFWApplication.h>
#include <GLFWCameraController.h>
#include <Light.h>
#include <SceneGraph.h>
#include <SceneView.h>

// Glm
#include <glm/glm.hpp>

using namespace gl;

static QuickGLFWApplication* Singleton = nullptr;

QuickGLFWApplication::QuickGLFWApplication(int width, int height) :
    m_application(nullptr),
    m_sceneGraph(new SceneGraph())
{
    if(Singleton != nullptr)
        throw std::runtime_error("Cannot create a second QuickGLFWApplication. Singleton pattern is used");

    m_application.reset(GLFWApplication::CreateWindow(width, height));

    std::shared_ptr<SceneView> sceneView(new SceneView());

    std::shared_ptr<Controller> controller(new GLFWCameraController(sceneView));
    sceneView->setInterface(controller);

    Rect rect(0,0,width,height);
    sceneView->setRect(rect);

    Light light;
    light.setColor(glm::vec3(1,0,0));
    light.setDirection(glm::vec3(-1,-1,-1));
    sceneView->setLight(light);

    sceneView->setScene(m_sceneGraph);

    m_application->addSceneView(sceneView);

    Singleton = this;
}

QuickGLFWApplication::~QuickGLFWApplication()
{
    GLFWApplication::Terminate();

    Singleton = nullptr;
}

QuickGLFWApplication* QuickGLFWApplication::Instance()
{
    return Singleton;
}

void QuickGLFWApplication::loop()
{
    this->m_application->loop();
}

Node* QuickGLFWApplication::root() const
{
    return m_sceneGraph->root();
}

SceneView* QuickGLFWApplication::sceneView() const
{
    return m_application->sceneViews().at(0).get();
}

void QuickGLFWApplication::setController(const std::shared_ptr<Controller> &controller)
{
    sceneView()->setInterface(controller);
}
