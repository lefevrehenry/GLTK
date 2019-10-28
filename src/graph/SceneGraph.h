#ifndef GLTK_SCENEGRAPH_H
#define GLTK_SCENEGRAPH_H

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <memory>


namespace gl {

class Node;
class Visitor;

/**
 * @brief The SceneGraph class
 */
class SceneGraph
{

public:
    SceneGraph();
    virtual ~SceneGraph() = default;

public:
    Node* root();
    const Node* root() const;

public:
    void getBB(glm::vec3& min, glm::vec3& max) const;

public:
    void executeVisitor(Visitor* visitor) const;

private:
    std::shared_ptr<Node> m_rootNode;

};

}   // namespace gl

#endif
