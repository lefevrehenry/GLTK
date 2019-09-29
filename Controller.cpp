#include "Controller.h"

#include "Camera.h"
#include "SceneGraph.h"
#include "SceneView.h"

using namespace gl;

Controller::~Controller()
{

}

DefaultController::DefaultController(std::weak_ptr<SceneView> sceneView) :
    m_sceneView(sceneView)
{

}

SceneView* DefaultController::sceneView() const
{
    std::shared_ptr<SceneView> sceneView(this->m_sceneView);

    if(sceneView)
        return sceneView.get();

    return nullptr;
}

SceneGraph* DefaultController::sceneGraph() const
{
    SceneView* sceneView = DefaultController::sceneView();

    if(sceneView)
        return sceneView->scene();

    return  nullptr;
}

Camera* DefaultController::camera() const
{
    SceneView* sceneView = DefaultController::sceneView();

    if(sceneView)
        return sceneView->camera();

    return  nullptr;
}
