#include "SceneGraph.h"

#include "Node.h"
#include "Visitor.h"

using namespace gl;

SceneGraph::SceneGraph() :
    m_rootNode(nullptr)
{
    this->m_rootNode = new Node();
}

SceneGraph::~SceneGraph()
{
    delete m_rootNode;
    m_rootNode = nullptr;
}

Node* SceneGraph::root()
{
    return m_rootNode;
}

const Node* SceneGraph::root() const
{
    return m_rootNode;
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
