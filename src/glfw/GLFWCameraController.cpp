#include "GLFWCameraController.h"

#include <Camera.h>
#include <SceneView.h>

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using namespace gl;

GLFWCameraController::GLFWCameraController(std::weak_ptr<SceneView> sceneView) : DefaultController (sceneView),
    mousePressed(false),
    last_x_position(-1),
    last_y_position(-1)
{

}

void GLFWCameraController::framebufferSizeCallback(GLFWwindow*, int width, int height)
{
    Camera* camera = DefaultController::camera();

    if(camera) {
        // Compute the aspect ratio of the size of the window
        float screen_aspect_ratio = float(width) / float(height);

        camera->setAspectRatio(screen_aspect_ratio);
    }

    glViewport(0, 0, width, height);
}

void GLFWCameraController::mouseButtonCallback(GLFWwindow* handle, int button, int action, int)
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

void GLFWCameraController::cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
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

void GLFWCameraController::scrollCallback(GLFWwindow*, double, double ypos)
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
