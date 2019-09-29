#include "CameraController.h"

#include "Camera.h"
#include "GLFWApplication.h"
#include "Mesh.h"
#include "Message.h"
#include "Node.h"
#include "SceneGraph.h"
#include "SceneView.h"
#include "Selectable.h"
#include "Visitor.h"
#include "VisualModel.h"

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/gtc/constants.hpp>


using namespace gl;

CameraController::CameraController(std::weak_ptr<SceneView> sceneView) : DefaultController (sceneView),
    mousePressed(false),
    last_x_position(-1),
    last_y_position(-1)
{

}

CameraController::~CameraController()
{

}

void CameraController::framebufferSizeCallback(GLFWwindow*, int width, int height)
{
    Camera* camera = DefaultController::camera();

    if(camera) {
        // Compute the aspect ratio of the size of the window
        float screen_aspect_ratio = float(width) / float(height);

        camera->setAspectRatio(screen_aspect_ratio);
    }

    glViewport(0, 0, width, height);
}

void CameraController::mouseButtonCallback(GLFWwindow* handle, int button, int action, int)
{
    this->mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos;
        double ypos;
        glfwGetCursorPos(handle, &xpos, &ypos);

        this->last_x_position = xpos;
        this->last_y_position = ypos;
    }
}

void CameraController::cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
{
    Camera* camera = DefaultController::camera();

    if (this->mousePressed && camera)
    {
        float dx = float(xpos - this->last_x_position);
        float dy = float(ypos - this->last_y_position);

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
        camera->rotate(rx, ry);
    }

    this->last_x_position = xpos;
    this->last_y_position = ypos;
}

void CameraController::scrollCallback(GLFWwindow*, double, double ypos)
{
    Camera* camera = DefaultController::camera();

    if(!camera)
        return;

    glm::vec3 eye = camera->eye();
    glm::vec3 target = camera->target();
    glm::vec3 up = camera->up();

    glm::vec3 newEye = eye + float(ypos) * 0.1f * (target - eye);

    camera->lookAt(newEye, target, up);
}

//InterfacePicking::InterfacePicking(SceneGraph* sceneGraph, Camera* camera) : CameraController (camera),
//    m_sceneGraph(sceneGraph),
//    m_pickingVisitor(nullptr),
//    m_cameraActive(false),
//    m_callback(nullptr)
//{
//    this->m_pickingVisitor = new PickingVisitor();
//}

//InterfacePicking::~InterfacePicking()
//{
//    delete m_pickingVisitor;
//    m_pickingVisitor = nullptr;
//}

//void InterfacePicking::setCallback(void (*callback)(const VisualModel*, glm::vec4))
//{
//    this->m_callback = callback;
//}

//void InterfacePicking::mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
//{
//    if(m_cameraActive)
//    {
//        CameraController::mouseButtonCallback(handle, button, action, mods);
//        return;
//    }

//    if (m_callback == nullptr)
//        return;

//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//    {
//        double x = 0;
//        double y = 0;
//        glfwGetCursorPos(handle, &x, &y);

//        y = GLFWApplication::ScreenHeight - y;

//        m_pickingVisitor->set(int(x), int(y));

//        const Node* root = this->m_sceneGraph->root();
//        root->executeVisitor(m_pickingVisitor);

//        const VisualModel* visualModel = m_pickingVisitor->selectedVisualModel();

//        const glm::vec3& ndc = m_pickingVisitor->selectedPosition();
//        const glm::mat4& projection = this->m_camera->projection();

//        glm::vec4 vs = glm::inverse(projection) * glm::vec4(ndc,1);
//        glm::vec4 ws = this->m_camera->model() * (vs / vs.w);

//        this->m_callback(visualModel, ws);
//    }
//}

//void InterfacePicking::keyCallback(GLFWwindow* handle, int key, int, int action, int)
//{
//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
//        this->m_cameraActive = true;

//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
//        this->m_cameraActive = false;

//    if (action == GLFW_PRESS)
//    {
//        switch(key) {
////        case GLFW_KEY_Q:
////            glfwSetWindowShouldClose(windowHandle, GL_TRUE);
////            break;
//        case GLFW_KEY_ESCAPE:
//            glfwSetWindowShouldClose(handle, GL_TRUE);
//            break;
//        default:
//            break;
//        }
//    }
//}
