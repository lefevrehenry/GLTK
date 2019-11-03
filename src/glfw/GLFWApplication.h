#ifndef GLTK_GLFWAPPLICATION_H
#define GLTK_GLFWAPPLICATION_H

#include <Application.h>
#include <Rect.h>

// Standard Library
#include <functional>
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
    void setBeforeDrawingCallback(std::function<void(float)> callback);
    void setAfterDrawingCallback(std::function<void(float)> callback);

public:
    GLFWwindow* getWindow() const;
    void setWindow(GLFWwindow* newHandle);

    Rect windowRect() const;
    void setWindowRect(const Rect& rect);

    void addSceneView(std::shared_ptr<SceneView> sceneView);

private:
    void draw();

public:
    static int OpenGLMajorVersion;
    static int OpenGLMinorVersion;

private:
    static GLFWApplication* OurInstance;

private:
    GLFWwindow* m_windowHandle;

    std::vector< std::shared_ptr<SceneView> > m_sceneViews;

    std::function<void(float)> m_beforeDrawing;
    std::function<void(float)> m_afterDrawing;

};

}   // namespace gl

#endif
