#include "Scene.h"

#include "Visitor.h"
#include "VisualModel.h"

using namespace gl;

Scene::Scene() :
    m_rootNode(),
    m_camera(Camera::Perspective),
    m_visualManager()
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

Camera* Scene::camera()
{
    return &m_camera;
}

void Scene::draw(Node* node)
{
    this->m_visualManager.updateUniformBufferCamera(this->m_camera);

    DrawVisitor drawVisitor(&m_visualManager);
    node->executeVisitor(&drawVisitor);
}

void Scene::draw()
{
    this->draw(root());
}

void Scene::getBbox(glm::vec3& min, glm::vec3& max) const
{
    BBoxVisitor boundingBoxVisitor;

    const Node* rootNode = root();
    rootNode->executeVisitor(&boundingBoxVisitor);

    min = boundingBoxVisitor.getMin();
    max = boundingBoxVisitor.getMax();
}

void Scene::pickingObject(double sx, double sy) const
{

}

//void Scene::draw(DrawStyle drawStyle)
//{
//    glPolygonMode(GL_FRONT_AND_BACK, drawStyle.polygonMode);

//    for (const Mesh* mesh : this->m_meshes) {
//        if (drawStyle.instanced > 1) {
//            mesh->drawInstanced(drawStyle.primitiveMode, drawStyle.instanced);
//        } else {
//            mesh->draw(drawStyle.primitiveMode);
//        }
//    }
//}

void Scene::fitCamera()
{
    glm::vec3 min;
    glm::vec3 max;
    this->getBbox(min, max);

    float diagonal = glm::length(max - min);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::vec3(0,0,-1) * diagonal);
    glm::vec3 up(0,1,0);
    this->m_camera.lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.2f * diagonal;
    float zFar = 2.0f * diagonal;
    this->m_camera.perspective(fovy, aspect, zNear, zFar);
}

