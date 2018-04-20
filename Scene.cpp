#include "Scene.h"

#include "Visitor.h"
#include "VisualModel.h"

using namespace gl;

Scene::Scene() :
    m_rootNode(),
    m_camera(),
    m_visualManager(),
    m_framebuffer(640,480),
    m_pickingVisitor()
{
    this->m_framebuffer.attachTexture();
    this->m_framebuffer.attachDepthTexture();
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
    glViewport(0, 0, 640, 480);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->draw(root());

    // draw into the framebuffer
    this->m_framebuffer.bind();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_visualManager.updateUniformBufferCamera(this->m_camera);

    Node* node = root();
    DrawVisitor drawVisitor(&m_visualManager);
    node->executeVisitor(&drawVisitor);

//    node->executeVisitor(&m_pickingVisitor);

    // draw the framebuffer
    float bounds[] = {320, 240, 320, 240};
    this->m_framebuffer.draw(bounds);
}

void Scene::getBbox(glm::vec3& min, glm::vec3& max) const
{
    BoundingBoxVisitor boundingBoxVisitor;

    const Node* rootNode = root();
    rootNode->executeVisitor(&boundingBoxVisitor);

    min = boundingBoxVisitor.getMin();
    max = boundingBoxVisitor.getMax();
}

void Scene::pickingObject(int sx, int sy) const
{
    sy = 480 - sy;

//    float bounds[4];
//    bounds[0] = sx / 640.0;
//    bounds[1] = (sx + 1) / 640.0;
//    bounds[2] = sy / 480.0;
//    bounds[3] = (sy + 1) / 480.0;

//    const glm::mat4& view = this->m_camera.view();
//    const glm::mat4& projection = this->m_camera.projectionROI(bounds);

//    glm::mat4 ViewProjMatrix = projection * view;
//    //const glm::mat4 mvp = this->m_camera.mvp();
//    this->m_pickingVisitor.setCamera(ViewProjMatrix);

//    this->m_framebuffer.bind();

//    // stack viewport
//    GLint bound[4];
//    glGetIntegerv(GL_VIEWPORT, &bound[0]);

//    glViewport(0,0,1,1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    const Node* node = root();
//    node->executeVisitor(&m_pickingVisitor);

//    // restore default viewport
//    glViewport(bound[0],bound[1],bound[2],bound[3]);

//    // read pixel
//    std::array<unsigned char, 4> indexComponents;
//    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, indexComponents.data());

//    msg_info("Debug") << +indexComponents[0] << "," << indexComponents[1] << "," << indexComponents[2] << "," << indexComponents[3];

//    this->m_framebuffer.unbind();
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

