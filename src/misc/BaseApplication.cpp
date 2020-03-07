#include "BaseApplication.h"

#include <AnimationGroup.h>
#include <SceneView.h>
#include <VisualManager.h>

using namespace gl;

unsigned int BaseApplication::ScreenWidth = 0;
unsigned int BaseApplication::ScreenHeight = 0;

BaseApplication::BaseApplication() :
    m_sceneViews(),
    m_animationsGroup(),
    m_beforeDrawing(),
    m_afterDrawing(),
    m_previousTime(0.0f)
{

}

BaseApplication::~BaseApplication()
{

}

void BaseApplication::draw()
{
    float currentTime = this->time();                      // seconds
    float dt = 1000.0 * (currentTime - m_previousTime);    // milliseconds

    float t = std::round(float(currentTime) * 100) / 100;
    VisualManager::UpdateUniformBufferTime(t);

    /* Call prepareFrame to update animations */
    this->prepareFrame(dt);

    /* Call beforeDrawing callback */
    this->callBeforeDrawingCallback(t);

    /* The actual draw */
    this->drawFrame();

    /* Call afterDrawing callback */
    this->callAfterDrawingCallback(t);

    /* Record the current time for the next frame */
    this->m_previousTime = currentTime;

}

BaseApplication::BeforeDrawingFunction BaseApplication::beforeDrawingCallback() const
{
    return this->m_beforeDrawing;
}

void BaseApplication::setBeforeDrawingCallback(BeforeDrawingFunction callback)
{
    this->m_beforeDrawing = callback;
}

void BaseApplication::callBeforeDrawingCallback(float t)
{
    if(this->m_beforeDrawing)
        this->m_beforeDrawing(t);
}

BaseApplication::AfterDrawingFunction BaseApplication::afterDrawingCallback() const
{
    return this->m_afterDrawing;
}

void BaseApplication::setAfterDrawingCallback(AfterDrawingFunction callback)
{
    this->m_afterDrawing = callback;
}

void BaseApplication::callAfterDrawingCallback(float t)
{
    if(this->m_afterDrawing)
        this->m_afterDrawing(t);
}

const std::vector< std::shared_ptr<SceneView> >& BaseApplication::sceneViews() const
{
    return this->m_sceneViews;
}

void BaseApplication::addSceneView(const std::shared_ptr<SceneView>& sceneView)
{
    this->m_sceneViews.push_back(sceneView);
}

const std::vector< std::shared_ptr<AnimationGroup> >& BaseApplication::animationsGroup() const
{
    return this->m_animationsGroup;
}

void BaseApplication::addAnimationGroup(const std::shared_ptr<AnimationGroup>& animationGroup)
{
    this->m_animationsGroup.push_back(animationGroup);
}

void BaseApplication::prepareFrame(double dt)
{
    for (std::shared_ptr<AnimationGroup>& animationGroup : m_animationsGroup) {
        if(animationGroup->running())
            animationGroup->update(dt);
    }
}

void BaseApplication::drawFrame()
{
    for (const std::shared_ptr<SceneView>& sceneView : sceneViews()) {
        if(sceneView)
            sceneView->draw();
    }
}
