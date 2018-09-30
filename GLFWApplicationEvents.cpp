#include "GLFWApplicationEvents.h"

#include "Camera.h"
#include "GLFWApplication.h"
#include "Selectable.h"
#include "Viewer.h"

#include "VisualModel.h"
#include "Mesh.h"
#include "Message.h"

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


using namespace gl;

GLFWApplicationEvents::GLFWApplicationEvents() : DefaultInterface(),
    mousePressed(false),
    x(-1),
    y(-1),
    m_camera(nullptr)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app && app->getViewer())
        this->m_camera = app->getViewer()->camera();
}

GLFWApplicationEvents::~GLFWApplicationEvents()
{

}

void GLFWApplicationEvents::mouseButtonCallback(GLFWwindow* handle, int button, int action, int /*mods*/)
{
    this->mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(handle, &xpos, &ypos);

        int sx = static_cast<int>(xpos);
        int sy = static_cast<int>(ypos);

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
    glm::vec3 neweye = this->m_camera->eye() - 5 * (float) ypos * this->m_camera->direction();
    glm::vec3 target(0,0,0);
    glm::vec3 up = this->m_camera->up();

    this->m_camera->lookAt(neweye, target, up);
}
