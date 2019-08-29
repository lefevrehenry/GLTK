#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include "CameraController.h"
#include "Viewport.h"

// Standard Library
#include <functional>
#include <memory>


namespace gl {

class Camera;
class Scene;
class Interface;

/**
 * @brief The SceneView class
 */
class SceneView
{
    using CameraType = CameraController::CameraType;

public:
    explicit SceneView(const Viewport& viewport, CameraType type = CameraType::None);
    explicit SceneView(int x, int y, int width, int height, CameraType type = CameraType::None);

public:
    const Viewport& viewport() const;
    void setViewport(const Viewport& viewport);

public:
    std::weak_ptr<Scene> scene() const;
    void setScene(std::weak_ptr<Scene> scene);

    std::weak_ptr<Camera> camera() const;
    void setCamera(std::weak_ptr<Camera> camera);

    const std::unique_ptr<Interface>& interface() const;
    void setInterface(CameraType type);

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
