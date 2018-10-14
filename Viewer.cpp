#include "Viewer.h"

#include "GLFWApplication.h"
#include "Framebuffer.h"
#include "Message.h"
#include "Node.h"
#include "Scene.h"
#include "Selectable.h"
#include "Visitor.h"
#include "VisualManager.h"

using namespace gl;

Viewer::Viewer(SceneGraph* scene) :
    m_camera(),
    m_scene(scene)
{
//    this->m_pickingFramebuffer.attachTexture();
//    this->m_pickingFramebuffer.attachDepthTexture();
}

Viewer::~Viewer()
{

}

Camera* Viewer::camera()
{
    return &m_camera;
}

SceneGraph* Viewer::scene() const
{
    return this->m_scene;
}

void Viewer::setScene(SceneGraph *scene)
{
    this->m_scene = scene;
}

void Viewer::draw(Node* node)
{
    VisualManager::UpdateUniformBufferCamera(this->m_camera);

    DrawVisitorWithSelection drawVisitor;
    node->executeVisitor(&drawVisitor);
}

void Viewer::draw()
{
    int width = (int) GLFWApplication::ScreenWidth;
    int height = (int) GLFWApplication::ScreenHeight;

    glViewport(0, 0, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Node* node = this->m_scene->root();
    this->draw(node);

//    // draw the framebuffer (debug)
//    float bounds[] = {0, 0, 320, 240};
//    this->m_pickingFramebuffer.draw(bounds);

//    GLuint nbPixelsQuery;
//    int nbPixel = -1;

//    glGenQueries(1, &nbPixelsQuery);
//    glBeginQuery(GL_SAMPLES_PASSED, nbPixelsQuery);

//    this->m_mesh->draw();

//    glEndQuery(GL_SAMPLES_PASSED);
//    glGetQueryObjectiv(nbPixelsQuery, GL_QUERY_RESULT, &nbPixel);
//    glDeleteQueries(1, &nbPixelsQuery);

//    msg_info("Draw") << nbPixel << " passed";
}

void Viewer::getBbox(glm::vec3& min, glm::vec3& max) const
{
    BoundingBoxVisitor boundingBoxVisitor;

    const Node* rootNode = this->m_scene->root();
    rootNode->executeVisitor(&boundingBoxVisitor);

    min = boundingBoxVisitor.getMin();
    max = boundingBoxVisitor.getMax();
}

void Viewer::fitCamera()
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

Selectable* Viewer::pickingObject(int sx, int sy)
{
    Selectable* selectable = nullptr;

    sy = 480 - sy;

//    float bounds[4];
//    bounds[0] = sx / 640.0;
//    bounds[1] = (sx + 1) / 640.0;
//    bounds[2] = sy / 480.0;
//    bounds[3] = (sy + 1) / 480.0;

    //const glm::mat4& view = this->m_camera.view();
    //const glm::mat4& projection = this->m_camera.projection();
    //this->m_camera.projectionROI(bounds);

    //glm::mat4 ViewProjMatrix = projection * view;
    //glm::mat4 ViewProjMatrix = this->m_camera.mvp();
    //this->m_pickingVisitor.setCamera(ViewProjMatrix);

    PickingVisitor pickingVisitor(sx, sy);

    Node* node = this->m_scene->root();
    node->executeVisitor(&pickingVisitor);

    const VisualModel* visual = pickingVisitor.selectedVisualModel();
    if (visual != nullptr) {
        selectable = new Selectable();
        selectable->setVisualModel(visual);
    }

    return selectable;

//        // stack viewport
//        GLint bound[4];
//        glGetIntegerv(GL_VIEWPORT, &bound[0]);

//        glViewport(0,0,1,1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        const Node* node = this->m_scene->root();
//        node->executeVisitor(&m_pickingVisitor);

//        // restore default viewport
//        glViewport(bound[0],bound[1],bound[2],bound[3]);

//        // read pixel
//        std::array<unsigned char, 4> indexComponents;
//        glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, indexComponents.data());

//        msg_info("Debug") << +indexComponents[0] << "," << indexComponents[1] << "," << indexComponents[2] << "," << indexComponents[3];
}
