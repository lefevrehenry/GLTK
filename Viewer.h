#ifndef VIEWER_H
#define VIEWER_H

#include "Camera.h"
#include "Framebuffer.h"
#include "Visitor.h"
#include "VisualManager.h"

// Glm
#include <glm/glm.hpp>


class GLFWwindow;

namespace gl {

class Node;
class Scene;

/**
 * @brief The Viewer class
 */
class Viewer
{

public:
    Viewer(Scene* scene);
    virtual ~Viewer();

public:
    Camera* camera();

public:
    void draw(Node* node);  // draw sub-graph
    void draw();            // draw scene graph from the root

public:
    void getBbox(glm::vec3& min, glm::vec3& max) const;
    void pickingObject(int sx, int sy);

public:
    void fitCamera();

public:
    void setScene(Scene* scene);

private:
    Camera m_camera;

    Framebuffer m_framebuffer;
    mutable PickingVisitor m_pickingVisitor;

    Scene* m_scene;

};

}   // namespace gl

#endif
