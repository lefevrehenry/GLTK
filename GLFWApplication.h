#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include "Application.h"
#include "Camera.h"
#include "ShaderProgram.h"


class GLFWwindow;

namespace gl {

class GLFWApplicationEvents;
class Interface;
class Mesh;

/**
 * @brief The GLFWApplication class
 */
class GLFWApplication : Application
{

friend class GLFWApplicationEvents;

public:
    static GLFWApplication* getInstance();

    static void mouseInput(GLFWwindow* handle, int button, int action, int mods);
    static void mousePos(GLFWwindow* handle, double xpos, double ypos);
    static void mouseScroll(GLFWwindow* handle, double xoffset, double yoffset);
    static void keyboardInput(GLFWwindow* handle, int key, int scancode, int action, int mods);

protected:
    GLFWApplication();
    virtual ~GLFWApplication();

public:

    virtual void init();

    virtual void loop();

    void draw();

private:
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    GLFWApplication(const GLFWApplication&) = delete;
    void operator=(const GLFWApplication&)  = delete;

public:

    GLFWwindow* getWindow() const;

    void setWindow(GLFWwindow* newHandle);

    Interface* getInterface() const;

    void setInterface(Interface* newInterface);

private:
    GLFWwindow* windowHandle;
    Interface* m_interface;

    const gl::Mesh* m_mesh;
    gl::ShaderProgram m_program;
    gl::ShaderProgram m_program_normal;
    Camera m_camera;

    //void (GLFWApplicationEvents::*cursorPosCallback) (double xpos, double ypos);

};

}   // namespace gl

#endif
