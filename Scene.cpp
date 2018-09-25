#include "Scene.h"

#include "Node.h"
#include "Visitor.h"

using namespace gl;

Scene::Scene() :
    m_rootNode(nullptr)
{
    this->m_rootNode = new Node();
}

Scene::~Scene()
{
    delete m_rootNode;
    m_rootNode = nullptr;
}

Node* Scene::root()
{
    return m_rootNode;
}

const Node* Scene::root() const
{
    return m_rootNode;
}

void Scene::executeVisitor(Visitor* visitor) const
{
    const Node* node = root();
    node->executeVisitor(visitor);
}
