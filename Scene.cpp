#include "Scene.h"

#include "Camera.h"
#include "Node.h"
#include "Visitor.h"

// Glm
#include <glm/glm.hpp>

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

void SceneGraph::fitView(Camera* camera) const
{
    BoundingBoxVisitor boundingBoxVisitor;

    m_rootNode->executeVisitor(&boundingBoxVisitor);

    glm::vec3 min = boundingBoxVisitor.getMin();
    glm::vec3 max = boundingBoxVisitor.getMax();

    float diagonal = glm::length(max - min);
    glm::vec3 direction(-1,-1,-1);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::normalize(direction) * diagonal);
    glm::vec3 up(0,0,1);
    camera->lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.02f * diagonal;
    float zFar = 2.0f * diagonal;
    camera->perspective(fovy, aspect, zNear, zFar);
//    float a = 160;
//    camera->orthographic(-a,a, -a/2,a/2, zNear, zFar);
}

void SceneGraph::executeVisitor(Visitor* visitor) const
{
    const Node* node = root();
    node->executeVisitor(visitor);
}
