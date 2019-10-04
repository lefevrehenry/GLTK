#include <graph/SceneGraph.h>

#include <graph/Node.h>
#include <graph/Visitor.h>

using namespace gl;

SceneGraph::SceneGraph() :
    m_rootNode(new Node())
{
}

Node* SceneGraph::root()
{
    return m_rootNode.get();
}

const Node* SceneGraph::root() const
{
    return m_rootNode.get();
}

void SceneGraph::getBB(glm::vec3& min, glm::vec3& max) const
{
    BoundingBoxVisitor boundingBoxVisitor;

    this->executeVisitor(&boundingBoxVisitor);

    min = boundingBoxVisitor.getMin();
    max = boundingBoxVisitor.getMax();
}

void SceneGraph::executeVisitor(Visitor* visitor) const
{
    const Node* node = root();
    node->executeVisitor(visitor);
}
