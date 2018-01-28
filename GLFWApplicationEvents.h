#ifndef GLFWAPPLICATIONEVENTS_H
#define GLFWAPPLICATIONEVENTS_H

#include "GLFWApplication.h"

// GLFW
#include <GLFW/glfw3.h>
#include <iostream>

// Glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>


class GLFWwindow;

namespace gl {

/**
 * @brief The Interface class
 */
class Interface
{

public:

    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) = 0;

    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos) = 0;

};

/**
 * @brief The GLFWApplicationEvents class
 */
class GLFWApplicationEvents : public Interface
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
            app->m_camera.rotate(rx, ry);
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
