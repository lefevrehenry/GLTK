#include "Scene.h"

#include "Visitor.h"
#include "VisualModel.h"

using namespace gl;

Scene::Scene() :
    m_rootNode(),
    m_camera(),
    m_visualManager(),
    m_framebuffer(1,1)
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
    BoundingBoxVisitor boundingBoxVisitor;

    const Node* rootNode = root();
    rootNode->executeVisitor(&boundingBoxVisitor);

    min = boundingBoxVisitor.getMin();
    max = boundingBoxVisitor.getMax();
}

void Scene::pickingObject(double sx, double sy) const
{
    //msg_info("a") << sx << ", " << s

    this->m_framebuffer.bind();

    // stack viewport
    GLint bound[4];
    glGetIntegerv(GL_VIEWPORT, &bound[0]);

    glViewport(0,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

//    PickingVisitor visitor(&m_visualManager);

    // restore default viewport
    glViewport(bound[0],bound[1],bound[2],bound[3]);

    this->m_framebuffer.unbind();
}

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

