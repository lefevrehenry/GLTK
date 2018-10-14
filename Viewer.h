#ifndef VIEWER_H
#define VIEWER_H

#include "Camera.h"

// Glm
#include <glm/glm.hpp>


class GLFWwindow;

namespace gl {

class Node;
class SceneGraph;
class Selectable;

/**
 * @brief The Viewer class
 */
class Viewer
{

public:
    Viewer(SceneGraph* scene);
    virtual ~Viewer();

public:
    Camera* camera();

public:
    SceneGraph* scene() const;
    void setScene(SceneGraph* scene);

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
    SceneGraph* m_scene;

};

}   // namespace gl

#endif
