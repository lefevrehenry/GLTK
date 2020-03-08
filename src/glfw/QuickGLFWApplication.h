#ifndef GLFW_QUICKGLFWAPPLICATION_H
#define GLFW_QUICKGLFWAPPLICATION_H

// Standard Library
#include <memory>


namespace gl {

class Controller;
class GLFWApplication;
class Node;
class SceneGraph;
class SceneView;

/**
 * @brief The QuickGLFWApplication class
 */
class QuickGLFWApplication
{

public:
    QuickGLFWApplication(int width, int height);
    virtual ~QuickGLFWApplication();

public:
    static QuickGLFWApplication* Instance();

public:
    void loop();

public:
    Node* root() const;
    SceneView* sceneView() const;

public:
    void setController(const std::shared_ptr<Controller>& controller);

private:
    std::shared_ptr<GLFWApplication>    m_application;
    std::shared_ptr<SceneGraph>         m_sceneGraph;

};

}   // namespace gl

#endif
