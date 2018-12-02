#ifndef SCENE_H
#define SCENE_H

// Glm
#include <glm/glm.hpp>


namespace gl {

class Camera;
class Node;
class Visitor;

/**
 * @brief The Scene class
 */
class SceneGraph
{

public:
    SceneGraph();
    virtual ~SceneGraph();

public:
    Node* root();
    const Node* root() const;

public:
    void getBB(glm::vec3& min, glm::vec3& max) const;

public:
    void executeVisitor(Visitor* visitor) const;

private:
    Node* m_rootNode;

};

}   // namespace gl

#endif
