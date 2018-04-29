#ifndef GLFWAPPLICATIONEVENTS_H
#define GLFWAPPLICATIONEVENTS_H

#include "Interface.h"


class GLFWwindow;

namespace gl {

/**
 * @brief The GLFWApplicationEvents class
 */
class GLFWApplicationEvents : public DefaultInterface
{

public:
    GLFWApplicationEvents();
    virtual ~GLFWApplicationEvents();

public:
    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos);

private:
    bool mousePressed;
    double x;
    double y;

};

}   // namespace gl

#endif
