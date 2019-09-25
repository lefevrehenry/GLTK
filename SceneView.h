#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include "CameraController.h"
#include "Viewport.h"

// Standard Library
#include <memory>


namespace gl {

class Camera;
class Interface;
class SceneGraph;
class Visitor;

/**
 * @brief The SceneView class
 */
class SceneView
{
    using CameraType = CameraController::CameraType;

public:
    explicit SceneView(const class Viewport& viewport);
    explicit SceneView(int x, int y, int width, int height);

public:
    const class Viewport& viewport() const;
    void setViewport(const class Viewport& viewport);

public:
    std::weak_ptr<SceneGraph> scene() const;
    void setScene(std::weak_ptr<SceneGraph> scene);

    std::weak_ptr<Camera> camera() const;
    void setCamera(std::weak_ptr<Camera> camera);

    const std::unique_ptr<Interface>& interface() const;
    void setInterface(CameraType type);

public:
    void draw() const;

private:
    class Viewport    m_viewport;

    std::weak_ptr<SceneGraph>   m_scene;
    std::shared_ptr<Camera>     m_camera;
    std::unique_ptr<Interface>  m_interface;
    std::shared_ptr<Visitor>    m_visitor;

};

}   // namespace gl

#endif
