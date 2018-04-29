#include "Scene.h"

#include "Visitor.h"

using namespace gl;

Scene::Scene() :
    m_rootNode()
{

}

Scene::~Scene()
{

}

Node* Scene::root()
{
    return &m_rootNode;
}

const Node* Scene::root() const
{
    return &m_rootNode;
}

void Scene::executeVisitor(Visitor* visitor) const
{
    const Node* node = root();
    node->executeVisitor(visitor);
}

