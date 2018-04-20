#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Framebuffer.h"
#include "Visitor.h"
#include "VisualManager.h"

// Glm
#include <glm/glm.hpp>


namespace gl {

class VisualModel;

/**
 * @brief The Scene class
 */
class Scene
{

public:
    Scene();
    virtual ~Scene();

public:
    Node* root();
    const Node* root() const;

    Camera* camera();

public:
    void draw(Node* node);  // draw sub-graph
    void draw();            // draw scene graph from the root

public:
    void getBbox(glm::vec3& min, glm::vec3& max) const;
    void pickingObject(int sx, int sy) const;

public:
    void fitCamera();

private:
    Node    m_rootNode;
    Camera  m_camera;

    VisualManager m_visualManager;

    Framebuffer m_framebuffer;
    mutable PickingVisitor m_pickingVisitor;

};

}   // namespace gl

#endif
