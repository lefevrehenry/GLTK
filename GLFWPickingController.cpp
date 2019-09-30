#include "GLFWPickingController.h"

#include "GLFWApplication.h"
#include "Node.h"
#include "SceneGraph.h"
#include "SceneView.h"
#include "Framebuffer.h"    // why ?? (Visitor.h should be suffisant)
#include "Visitor.h"
#include "VisualModel.h"

// Glfw
#include <GLFW/glfw3.h>

using namespace gl;

GLFWPickingController::GLFWPickingController(std::weak_ptr<SceneView> sceneView) : GLFWCameraController (sceneView),
    m_pickingVisitor(new PickingVisitor()),
    m_cameraActive(false),
    m_callback(nullptr)
{
}

void GLFWPickingController::setCallback(void (*callback)(const VisualModel*, glm::vec4))
{
    this->m_callback = callback;
}

void GLFWPickingController::mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    if(m_cameraActive)
    {
        GLFWCameraController::mouseButtonCallback(handle, button, action, mods);
        return;
    }

    if (m_callback == nullptr)
        return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x = 0;
        double y = 0;
        glfwGetCursorPos(handle, &x, &y);

        y = GLFWApplication::ScreenHeight - y;

        m_pickingVisitor->set(int(x), int(y));

        SceneGraph* sceneGraph = DefaultController::sceneGraph();
        Camera* camera = DefaultController::camera();

        if(!sceneGraph || !camera)
            return;

        const Node* root = sceneGraph->root();
        root->executeVisitor(m_pickingVisitor.get());

        const VisualModel* visualModel = m_pickingVisitor->selectedVisualModel();

        const glm::vec3& ndc = m_pickingVisitor->selectedPosition();
        const glm::mat4& projection = camera->projection();

        glm::vec4 vs = glm::inverse(projection) * glm::vec4(ndc,1);
        glm::vec4 ws = camera->model() * (vs / vs.w);

        this->m_callback(visualModel, ws);
    }
}

void GLFWPickingController::keyCallback(GLFWwindow* handle, int key, int, int action, int)
{
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
        this->m_cameraActive = true;

    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
        this->m_cameraActive = false;

    if (action == GLFW_PRESS)
    {
        switch(key) {
//        case GLFW_KEY_Q:
//            glfwSetWindowShouldClose(windowHandle, GL_TRUE);
//            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(handle, GL_TRUE);
            break;
        default:
            break;
        }
    }
}
