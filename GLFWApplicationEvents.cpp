#include "GLFWApplicationEvents.h"

#include "GLFWApplication.h"
#include "Viewer.h"

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>


using namespace gl;

GLFWApplicationEvents::GLFWApplicationEvents() :
    mousePressed(false),
    x(-1),
    y(-1)
{

}

GLFWApplicationEvents::~GLFWApplicationEvents()
{

}

void GLFWApplicationEvents::mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    this->mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(handle, &xpos, &ypos);
        //GLFWApplication* app = GLFWApplication::getInstance();
        //app->getViewer()->pickingObject(xpos, ypos);
    }
}

void GLFWApplicationEvents::cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
{
    if (this->mousePressed) {
        double dx = xpos - this->x;
        double dy = ypos - this->y;
        int width = 0;
        int height = 0;
        glfwGetWindowSize(handle, &width, &height);
        float pi = glm::pi<float>();
        float rx = ( dx / width) * (2.0 * pi);
        float ry = (-dy / height) * pi;
        GLFWApplication* app = GLFWApplication::getInstance();
        app->getViewer()->camera()->rotate(rx, ry);
    }
    this->x = xpos;
    this->y = ypos;
}
