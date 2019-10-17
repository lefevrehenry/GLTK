#ifndef GLFWPICKINGCONTROLLER_H
#define GLFWPICKINGCONTROLLER_H

#include "GLFWCameraController.h"

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <memory>


class GLFWwindow;

namespace gl {

class PickingVisitor;
class SceneView;
class VisualModel;

/**
 * @brief The GLFWPickingController class
 */
class GLFWPickingController : public GLFWCameraController
{

public:
    GLFWPickingController(std::weak_ptr<SceneView> sceneView);

public:
    void setCallback(void (*callback)(std::shared_ptr<const VisualModel>, glm::vec4));

public:
    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
    virtual void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

private:
    std::shared_ptr<PickingVisitor> m_pickingVisitor;
    bool                            m_cameraActive;

    void (*m_callback)(std::shared_ptr<const VisualModel>, glm::vec4);

};

}   // namespace gl

#endif
