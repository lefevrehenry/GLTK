#ifndef GLTK_BASEAPPLICATION_H
#define GLTK_BASEAPPLICATION_H

#include <Rect.h>

// Standard Library
#include <functional>
#include <memory>
#include <vector>


namespace gl {

class AnimationGroup;
class SceneView;

/**
 * @brief The BaseApplication class
 */
class BaseApplication
{

public:
    using BeforeDrawingFunction = std::function<void(float)>;
    using AfterDrawingFunction = std::function<void(float)>;

protected:
    BaseApplication();
    virtual ~BaseApplication();

protected:
    void draw();

public:
    virtual float time() const = 0;
    virtual void loop() = 0;

public:
    virtual Rect windowRect() const = 0;
    virtual void setWindowRect(const Rect& rect) = 0;

public:
    BeforeDrawingFunction beforeDrawingCallback() const;
    void setBeforeDrawingCallback(BeforeDrawingFunction callback);
    void callBeforeDrawingCallback(float t);

    AfterDrawingFunction afterDrawingCallback() const;
    void setAfterDrawingCallback(AfterDrawingFunction callback);
    void callAfterDrawingCallback(float t);

public:
    const std::vector< std::shared_ptr<SceneView> >& sceneViews() const;
    void addSceneView(const std::shared_ptr<SceneView>& sceneView);

    const std::vector< std::shared_ptr<AnimationGroup> >& animationsGroup() const;
    void addAnimationGroup(const std::shared_ptr<AnimationGroup>& animationGroup);

private:
    virtual void prepareFrame(double dt);
    virtual void drawFrame();

public:
    static unsigned int ScreenWidth;
    static unsigned int ScreenHeight;

private:
    BaseApplication(const BaseApplication&)     = delete;
    void operator=(const BaseApplication&)  = delete;

private:
    std::vector< std::shared_ptr<SceneView> >       m_sceneViews;
    std::vector< std::shared_ptr<AnimationGroup> >  m_animationsGroup;

    BeforeDrawingFunction   m_beforeDrawing;
    AfterDrawingFunction    m_afterDrawing;

    float m_previousTime;

};

}   // namespace gl

#endif
