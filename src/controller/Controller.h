#ifndef INTERFACE_H
#define INTERFACE_H

// Standard Library
#include <memory>


class GLFWwindow;

namespace gl {

class Camera;
class SceneGraph;
class SceneView;

/**
 * @brief The Controller class
 */
class Controller
{

public:
    virtual ~Controller();

public:
    virtual void framebufferSizeCallback(GLFWwindow* handle, int width, int height) = 0;
    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) = 0;
    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos) = 0;
    virtual void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset) = 0;
    virtual void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) = 0;

};

/**
 * @brief The DefaultCntroller class
 */
class DefaultController : public Controller
{

public:
    DefaultController(std::weak_ptr<SceneView> sceneView);
    virtual ~DefaultController() = default;

public:
    virtual void framebufferSizeCallback(GLFWwindow*, int, int) {}
    virtual void mouseButtonCallback(GLFWwindow*, int, int, int) {}
    virtual void cursorPosCallback(GLFWwindow*, double, double) {}
    virtual void scrollCallback(GLFWwindow*, double, double) {}
    virtual void keyCallback(GLFWwindow*, int, int, int, int) {}

public:
    SceneView* sceneView() const;
    SceneGraph* sceneGraph() const;
    Camera* camera() const;

private:
    std::weak_ptr<SceneView> m_sceneView;

};

}   // namespace gl

#endif
