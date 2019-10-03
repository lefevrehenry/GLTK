#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include "Rect.h"

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

public:
    explicit SceneView();

public:
    const misc::Rect& rect() const;
    void setRect(const misc::Rect& rect);

    glm::vec4 backgroundColor() const;
    void setBackgroundColor(const glm::vec4& backgroundColor);

public:
    SceneGraph* scene() const;
    void setScene(std::weak_ptr<SceneGraph> scene);

    Camera* camera() const;
    void setCamera(std::weak_ptr<Camera> camera);

    const std::shared_ptr<Controller>& interface() const;
    void setInterface(const std::shared_ptr<Controller>& interface);

public:
    void draw() const;

private:
    misc::Rect  m_rect;
    glm::vec4   m_backgroundcolor;

    std::weak_ptr<SceneGraph>   m_scene;
    std::shared_ptr<Camera>     m_camera;
    std::shared_ptr<Controller> m_interface;
    std::shared_ptr<Visitor>    m_visitor;

};

}   // namespace gl

#endif
