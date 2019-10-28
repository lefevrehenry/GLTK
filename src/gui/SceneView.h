#ifndef GLTK_SCENEVIEW_H
#define GLTK_SCENEVIEW_H

#include <Light.h>
#include <Rect.h>

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
    const Rect& rect() const;
    void setRect(const Rect& rect);

    glm::vec4 backgroundColor() const;
    void setBackgroundColor(const glm::vec4& backgroundColor);

    Light light() const;
    void setLight(const Light& light);

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
    Rect        m_rect;
    glm::vec4   m_backgroundcolor;
    Light       m_light;

    std::weak_ptr<SceneGraph>   m_scene;
    std::shared_ptr<Camera>     m_camera;
    std::shared_ptr<Controller> m_interface;
    std::shared_ptr<Visitor>    m_visitor;

};

}   // namespace gl

#endif
