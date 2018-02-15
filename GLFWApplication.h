#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include "Application.h"
#include "Camera.h"


class GLFWwindow;

namespace gl {

class GLFWApplicationEvents;
class Interface;
class Mesh;
class Program;

/**
 * @brief The GLFWApplication class
 */
class GLFWApplication : Application
{

friend class GLFWApplicationEvents;
friend class ShaderProgram;

public:
    static GLFWApplication* getInstance();

    static void FramebufferSizeCallback(GLFWwindow* handle, int width, int height);
    static void MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* handle, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* handle, double xoffset, double yoffset);
    static void KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

protected:
    GLFWApplication();
    virtual ~GLFWApplication();

public:

    virtual void init();

    virtual void loop();

    void draw();

private:
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    GLFWApplication(const GLFWApplication&) = delete;
    void operator=(const GLFWApplication&)  = delete;

public:

    GLFWwindow* getWindow() const;

    void setWindow(GLFWwindow* newHandle);

    Interface* getInterface() const;

    void setInterface(Interface* newInterface);

    Camera* getCamera();

private:
    GLFWwindow* windowHandle;
    Interface* m_interface;

    const gl::Mesh* m_mesh;
    Camera m_camera;

};

}   // namespace gl

#endif
