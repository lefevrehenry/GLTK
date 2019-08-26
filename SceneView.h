#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include "Viewport.h"
#include "GLFWApplicationEvents.h"

// Standard Library
#include <functional>
#include <memory>


namespace gl {

class Camera;
class Scene;
class Interface;

class SceneView
{

public:
    explicit SceneView(const Viewport& viewport);
    explicit SceneView(int x, int y, int width, int height);

public:
    const Viewport& viewport() const;
    void setViewport(const Viewport& viewport);

public:
    std::weak_ptr<Scene> scene() const;
    void setScene(std::weak_ptr<Scene> scene);

    std::weak_ptr<Camera> camera() const;
    void setCamera(std::weak_ptr<Camera> camera);

//    const std::unique_ptr<Interface>& interface() const;
    void setInterface(CameraController::CameraType type)
    {
        BaseCameraControllerCreator* creator = CameraController::Create(type);

        this->m_interface.reset(creator->create());

        delete creator;
    }

public:
    void setDrawCallback(std::function<void()> drawCallback);

public:
    void draw() const;

private:
    Viewport    m_viewport;

    std::shared_ptr<Scene>      m_scene;
    std::shared_ptr<Camera>     m_camera;
    std::unique_ptr<Interface>  m_interface;

    std::function<void()>   m_drawCallback;

};

}   // namespace gl

#endif
