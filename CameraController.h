#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Controller.h"

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <memory>
#include <utility>


class GLFWwindow;

namespace gl {

class Camera;
class PickingVisitor;
class SceneGraph;
class VisualModel;

/**
 * @brief The CameraController class
 */
class CameraController : public DefaultController
{

public:
    CameraController(std::weak_ptr<SceneView> sceneView);
    virtual ~CameraController();

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

/**
 * @brief The InterfacePicking class
 */
//class InterfacePicking : public CameraController
//{

//public:
//    InterfacePicking(SceneGraph* sceneGraph, Camera* camera);
//    virtual ~InterfacePicking();

//public:
//    void setCallback(void (*callback)(const VisualModel*, glm::vec4));

//public:
//    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
//    virtual void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

//private:
//    SceneGraph* m_sceneGraph;
//    PickingVisitor* m_pickingVisitor;
//    bool m_cameraActive;

//    void (*m_callback)(const VisualModel*, glm::vec4);
//};

}   // namespace gl

#endif
