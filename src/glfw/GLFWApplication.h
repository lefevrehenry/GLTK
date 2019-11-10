#ifndef GLTK_GLFWAPPLICATION_H
#define GLTK_GLFWAPPLICATION_H

#include <Application.h>
#include <Rect.h>


class GLFWwindow;

namespace gl {

/**
 * @brief The GLFWApplication class
 */
class GLFWApplication : public Application
{

public:
    static GLFWApplication* Instance();

    static GLFWApplication* CreateWindow(int width, int height);
    static void Terminate();

    static void FramebufferSizeCallback(GLFWwindow* handle, int width, int height);
    static void MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* handle, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* handle, double xoffset, double yoffset);
    static void KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

protected:
    GLFWApplication(GLFWwindow* handle);
    virtual ~GLFWApplication();

public:
    virtual void init();
    virtual void loop();

public:
    GLFWwindow* getWindow() const;
    void setWindow(GLFWwindow* newHandle);

    Rect windowRect() const;
    void setWindowRect(const Rect& rect);

private:
    void draw();

public:
    static int OpenGLMajorVersion;
    static int OpenGLMinorVersion;

private:
    static GLFWApplication* OurInstance;

private:
    GLFWwindow* m_windowHandle;
    double      m_previousTime;

};

}   // namespace gl

#endif
