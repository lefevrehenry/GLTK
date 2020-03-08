#ifndef GLTK_GLFWAPPLICATION_H
#define GLTK_GLFWAPPLICATION_H

#include <BaseApplication.h>
#include <Rect.h>


class GLFWwindow;

namespace gl {

/**
 * @brief The GLFWApplication class
 */
class GLFWApplication : public BaseApplication
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

public:
    virtual ~GLFWApplication();

public:
    float time() const override;
    void loop() override;

public:
    Rect windowRect() const override;
    void setWindowRect(const Rect& rect) override;

public:
    GLFWwindow* getWindow() const;
    void setWindow(GLFWwindow* newHandle);

public:
    static int OpenGLMajorVersion;
    static int OpenGLMinorVersion;

private:
    static GLFWApplication* OurInstance;

private:
    GLFWwindow* m_windowHandle;

};

}   // namespace gl

#endif
