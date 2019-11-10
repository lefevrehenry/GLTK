#include "Application.h"

using namespace gl;

unsigned int Application::ScreenWidth = 0;
unsigned int Application::ScreenHeight = 0;

Application::Application() :
    m_sceneViews(),
    m_animationsGroup(),
    m_beforeDrawing(),
    m_afterDrawing()
{

}

Application::~Application()
{

}

void Application::prepareFrame(double dt)
{
    for (AnimationGroup& animationGroup : m_animationsGroup)
        animationGroup.update(dt);
}

std::function<void (float)> Application::beforeDrawingCallback() const
{
    return this->m_beforeDrawing;
}

void Application::setBeforeDrawingCallback(std::function<void (float)> callback)
{
    this->m_beforeDrawing = callback;
}

void Application::callBeforeDrawingCallback(float t)
{
    if(this->m_beforeDrawing)
        this->m_beforeDrawing(t);
}

std::function<void (float)> Application::afterDrawingCallback() const
{
    return this->m_afterDrawing;
}

void Application::setAfterDrawingCallback(std::function<void (float)> callback)
{
    this->m_afterDrawing = callback;
}

void Application::callAfterDrawingCallback(float t)
{
    if(this->m_afterDrawing)
        this->m_afterDrawing(t);
}

const std::vector<std::shared_ptr<SceneView> >& Application::sceneViews() const
{
    return this->m_sceneViews;
}

void Application::addSceneView(std::shared_ptr<SceneView> sceneView)
{
    this->m_sceneViews.push_back(sceneView);
}

const std::vector<AnimationGroup>& Application::animationsGroup() const
{
    return this->m_animationsGroup;
}

void Application::addAnimationGroup(AnimationGroup animationGroup)
{
    this->m_animationsGroup.push_back(animationGroup);
}
