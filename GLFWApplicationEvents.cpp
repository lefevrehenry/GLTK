#include "GLFWApplicationEvents.h"

#include "Camera.h"
#include "GLFWApplication.h"
#include "Mesh.h"
#include "Message.h"
#include "Node.h"
#include "Scene.h"
#include "Selectable.h"
#include "Visitor.h"
#include "VisualModel.h"

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


using namespace gl;

GLFWApplicationEvents::GLFWApplicationEvents(Camera* camera) : DefaultInterface(),
    mousePressed(false),
    x(-1),
    y(-1),
    m_camera(camera)
{
}

GLFWApplicationEvents::~GLFWApplicationEvents()
{

}

void GLFWApplicationEvents::mouseButtonCallback(GLFWwindow* handle, int button, int action, int /*mods*/)
{
    this->mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//        double xpos, ypos;
        glfwGetCursorPos(handle, &x, &y);

//        int sx = static_cast<int>(xpos);
//        int sy = static_cast<int>(ypos);

//        GLFWApplication* app = GLFWApplication::getInstance();
//        Selectable* selectable = app->getViewer()->pickingObject(sx, sy);

//        if (selectable != nullptr) {
//            msg_info("Debug") << selectable->visualModel()->mesh()->name();
//        }

//        app->setSelected(selectable);
    }
}

void GLFWApplicationEvents::cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
{
    if (this->mousePressed && this->m_camera)
    {
        float dx = static_cast<float>(xpos - this->x);
        float dy = static_cast<float>(ypos - this->y);

//        int width = 0;
//        int height = 0;
//        glfwGetWindowSize(handle, &width, &height);

//        float near = this->m_camera->near();
//        float far = this->m_camera->far();

//        dx = 2 * (dx / width) - 1;
//        dy = 2 * (dy / height) - 1;
//        glm::vec4 ndc(dx,dy,-1,1);
//        float w = -near;
//        glm::vec4 clip = glm::vec4(ndc.x * w, ndc.y * w, ndc.z * w, w);

//        glm::mat4 inverse_proj = glm::inverse( this->m_camera->projection() );
//        glm::mat4 inverse_view = glm::inverse( this->m_camera->view() );

//        glm::vec4 v = inverse_view * inverse_proj * clip;

//        glm::vec3 dir = glm::mat3(this->m_camera->model()) * glm::vec3(dx,-dy,0);
//        this->m_camera->translate(-glm::vec3(v));

        int width = 0;
        int height = 0;
        glfwGetWindowSize(handle, &width, &height);
        float pi = glm::pi<float>();
        float rx = ( dx / width) * (2.0f * pi);
        float ry = (-dy / height) * pi;
        this->m_camera->rotate(rx, ry);
    }

    this->x = xpos;
    this->y = ypos;
}

void GLFWApplicationEvents::scrollCallback(GLFWwindow*, double, double ypos)
{
    glm::vec3 eye = this->m_camera->eye();
    glm::vec3 target = this->m_camera->target();
    glm::vec3 up = this->m_camera->up();

    glm::vec3 newEye = eye + (float) ypos * 0.1f * (target - eye);

    this->m_camera->lookAt(newEye, target, up);
}

InterfacePicking::InterfacePicking(SceneGraph* sceneGraph, Camera *camera) : GLFWApplicationEvents (camera),
    m_sceneGraph(sceneGraph),
    m_pickingVisitor(nullptr),
    m_cameraActive(false),
    m_callback(nullptr)
{
    this->m_pickingVisitor = new PickingVisitor();
}

InterfacePicking::~InterfacePicking()
{
    delete m_pickingVisitor;
    m_pickingVisitor = nullptr;
}

void InterfacePicking::setCallback(void (*callback)(const VisualModel*))
{
    this->m_callback = callback;
}

void InterfacePicking::mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    if(m_cameraActive)
    {
        GLFWApplicationEvents::mouseButtonCallback(handle, button, action, mods);
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x = 0;
        double y = 0;
        glfwGetCursorPos(handle, &x, &y);

        m_pickingVisitor->set((int) x, (int) y);

        const Node* root = this->m_sceneGraph->root();
        root->executeVisitor(m_pickingVisitor);

        const VisualModel* visualModel = m_pickingVisitor->selectedVisualModel();
        const glm::vec3& ndc = m_pickingVisitor->selectedPosition();

        const glm::mat4& projection = this->m_camera->projection();
        glm::vec4 vs = glm::inverse(projection) * glm::vec4(ndc,1);
        vs /= vs.w;

        glm::vec4 ws = this->m_camera->model() * vs;

        if (m_callback != nullptr)
            m_callback(visualModel);
    }
}

void InterfacePicking::keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
        this->m_cameraActive = true;

    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
        this->m_cameraActive = false;
}
