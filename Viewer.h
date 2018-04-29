#ifndef VIEWER_H
#define VIEWER_H

#include "Camera.h"

// Glm
#include <glm/glm.hpp>


class GLFWwindow;

namespace gl {

class Node;
class Scene;
class Selectable;

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
    Scene* scene() const;
    void setScene(Scene* scene);

public:
    void draw(Node* node);  // draw sub-graph
    void draw();            // draw scene graph from the root

public:
    void getBbox(glm::vec3& min, glm::vec3& max) const;
    void fitCamera();

public:
    Selectable* pickingObject(int sx, int sy);

private:
    Camera m_camera;
    Scene* m_scene;

};

}   // namespace gl

#endif
