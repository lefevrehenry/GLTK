#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
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
    Camera* camera();

public:
    void draw(Node* node);  // draw sub-graph
    void draw();            // draw scene graph from the root

public:
//    void addMesh(const Mesh* mesh);
//    void addMesh(const std::string& filename);
    void getBbox(glm::vec3& min, glm::vec3& max) const;
//    void draw(gl::DrawStyle drawStyle);

public:
    void fitCamera();

private:
    Node    m_rootNode;
    Camera  m_camera;

    VisualManager m_visualManager;

};

}   // namespace gl

#endif