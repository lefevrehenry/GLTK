#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include "Application.h"


class GLFWwindow;

namespace gl {

class GLFWApplicationEvents;
class Interface;

/**
 * @brief The GLFWApplication class
 */
class GLFWApplication : public Application
{

public:
    static GLFWApplication* getInstance();

    static GLFWApplication* CreateWindow();
    static void Terminate();

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

public:
    GLFWwindow* getWindow() const;
    void setWindow(GLFWwindow* newHandle);

    Interface* getInterface() const;
    void setInterface(Interface* interface);

    void setDrawCallBack(void (*drawCallback)());

public:
    static unsigned int ScreenWidth;
    static unsigned int ScreenHeight;

    static int OpenGLMajorVersion;
    static int OpenGLMinorVersion;

private:
    static GLFWApplication* OurInstance;

private:

    GLFWwindow* windowHandle;

    Interface* m_interface;

    void (*m_drawCallback)();

};

}   // namespace gl

#endif
