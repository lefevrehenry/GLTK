#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include "CameraController.h"
#include "Viewport.h"

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <memory>


namespace gl {

class Camera;
class Controller;
class SceneGraph;
class Visitor;

/**
 * @brief The SceneView class
 */
class SceneView
{
    using CameraType = CameraController::CameraType;

public:
    explicit SceneView();

public:
    const class Viewport& viewport() const;
    void setViewport(const class Viewport& viewport);

    glm::vec4 backgroundColor() const;
    void setBackgroundColor(const glm::vec4& backgroundColor);

public:
    SceneGraph* scene() const;
    void setScene(std::weak_ptr<SceneGraph> scene);

    Camera* camera() const;
    void setCamera(std::weak_ptr<Camera> camera);

    const std::unique_ptr<Controller>& interface() const;
    void setInterface(CameraType type);

public:
    void draw() const;

private:
    class Viewport  m_viewport;
    glm::vec4       m_backgroundcolor;

    std::weak_ptr<SceneGraph>   m_scene;
    std::shared_ptr<Camera>     m_camera;
    std::unique_ptr<Controller> m_interface;
    std::shared_ptr<Visitor>    m_visitor;

};

}   // namespace gl

#endif
