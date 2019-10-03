#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include "Application.h"
#include "Viewport.h"

// Standard Library
#include <memory>
#include <vector>


class GLFWwindow;

namespace gl {

class SceneView;

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

    misc::Rect windowSize() const;

    void addSceneView(std::shared_ptr<SceneView> sceneView);

private:
    void draw();

public:
    static unsigned int ScreenWidth;
    static unsigned int ScreenHeight;

    static int OpenGLMajorVersion;
    static int OpenGLMinorVersion;

private:
    static GLFWApplication* OurInstance;

private:
    GLFWwindow* m_windowHandle;

    std::vector< std::shared_ptr<SceneView> > m_sceneViews;

};

}   // namespace gl

#endif
