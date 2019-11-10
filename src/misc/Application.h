#ifndef GLTK_APPLICATION_H
#define GLTK_APPLICATION_H

// Standard Library
#include <functional>
#include <memory>
#include <vector>


namespace gl {

class SceneView;

/**
 * @brief The Application class
 */
class Application
{

protected:
    Application();
    virtual ~Application();

public:
    virtual void init() = 0;
    virtual void loop() = 0;

protected:
    void prepareFrame(double dt);

public:
    std::function<void(float)> beforeDrawingCallback() const;
    void setBeforeDrawingCallback(std::function<void (float)> callback);
    void callBeforeDrawingCallback(float t);

    std::function<void(float)> afterDrawingCallback() const;
    void setAfterDrawingCallback(std::function<void (float)> callback);
    void callAfterDrawingCallback(float t);

public:
    const std::vector< std::shared_ptr<SceneView> >& sceneViews() const;
    void addSceneView(std::shared_ptr<SceneView> sceneView);

public:
    static unsigned int ScreenWidth;
    static unsigned int ScreenHeight;

private:
    Application(const Application&)     = delete;
    void operator=(const Application&)  = delete;

private:
    std::vector< std::shared_ptr<SceneView> > m_sceneViews;

    std::function<void(float)> m_beforeDrawing;
    std::function<void(float)> m_afterDrawing;

};

}   // namespace gl

#endif
