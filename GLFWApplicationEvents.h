#ifndef GLFWAPPLICATIONEVENTS_H
#define GLFWAPPLICATIONEVENTS_H

#include "GLFWApplication.h"
#include "Interface.h"
#include "Scene.h"

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>


class GLFWwindow;

namespace gl {

/**
 * @brief The GLFWApplicationEvents class
 */
class GLFWApplicationEvents : public DefaultInterface
{

public:

    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
    {
        this->mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
    }

    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
    {
        if (mousePressed) {
            double dx = xpos - this->x;
            double dy = ypos - this->y;
            int width = 0;
            int height = 0;
            glfwGetWindowSize(handle, &width, &height);
            float pi = glm::pi<float>();
            float rx = ( dx / width) * (2.0 * pi);
            float ry = (-dy / height) * pi;
            GLFWApplication* app = GLFWApplication::getInstance();
            app->getScene()->camera()->rotate(rx, ry);
        }
        this->x = xpos;
        this->y = ypos;
    }

private:

    bool mousePressed;
    double x;
    double y;

};

}   // namespace gl

#endif
