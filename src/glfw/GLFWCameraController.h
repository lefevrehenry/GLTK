#ifndef GLTK_GLFWCAMERACONTROLLER_H
#define GLTK_GLFWCAMERACONTROLLER_H

#include <Controller.h>

// Standard Library
#include <memory>


class GLFWwindow;

namespace gl {

class SceneView;

/**
 * @brief The GLFWCameraController class
 */
class GLFWCameraController : public DefaultController
{

public:
    GLFWCameraController(std::weak_ptr<SceneView> sceneView);

public:
    virtual void framebufferSizeCallback(GLFWwindow* handle, int width, int height);
    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos);
    virtual void scrollCallback(GLFWwindow* handle, double xpos, double ypos);

private:
    bool mousePressed;
    double last_x_position;
    double last_y_position;

};

}   // namespace gl

#endif
