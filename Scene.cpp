#include "Scene.h"


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

void Scene::pickObject(int sx, int sy) const
{

}

