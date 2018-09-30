#ifndef GLFWAPPLICATIONEVENTS_H
#define GLFWAPPLICATIONEVENTS_H

#include "Interface.h"


class GLFWwindow;

namespace gl {

class Camera;

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
    virtual void scrollCallback(GLFWwindow* handle, double xpos, double ypos);

private:
    bool mousePressed;
    double x;
    double y;
    Camera* m_camera;

};

}   // namespace gl

#endif
