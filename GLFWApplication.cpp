#include "GLFWApplication.h"

#include "GLFWApplicationEvents.h"
#include "Message.h"
#include "Scene.h"
#include "Selectable.h"
#include "Viewer.h"
#include "VisualManager.h"

// OpenGL
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace gl;

unsigned int GLFWApplication::ScreenWidth = 640;
unsigned int GLFWApplication::ScreenHeight = 480;

int GLFWApplication::OpenGLMajorVersion = 3;
int GLFWApplication::OpenGLMinorVersion = 3;

GLFWApplication* GLFWApplication::OurInstance = nullptr;

GLFWApplication* GLFWApplication::getInstance()
{
    return OurInstance;
}

GLFWApplication* GLFWApplication::CreateWindow()
{
    if (OurInstance != nullptr) {
        msg_error("GLFWApplication") << "Cannot create a second GLFWApplication. Singleton pattern is used";
        return nullptr;
    }

    /* GLFW initialization */
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWApplication::OpenGLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWApplication::OpenGLMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = (int) GLFWApplication::ScreenWidth;
    int height = (int) GLFWApplication::ScreenHeight;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* windowHandle = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

    if (!windowHandle)
    {
        glfwTerminate();
        msg_error("GLFW") << "Cannot create a window and its opengl context";
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(windowHandle);

    // Glew initialization
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        // Problem: glewInit failed, something is seriously wrong.
        msg_error("OpenGL") << "Glew init failed";
        return nullptr;
    }

    GLFWApplication* app = new GLFWApplication();
    app->setWindow(windowHandle);

    VisualManager::Init();

    // Specifies background color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // Enable depth buffer test
    glEnable(GL_DEPTH_TEST);
    // Enable eliminaton of hidden faces
    glEnable(GL_CULL_FACE);
    // Specifies whether front or back facing facets are candidates for culling
    glCullFace(GL_BACK);
    // Specifies the orientation of front-facing polygons
    glFrontFace(GL_CCW);

    /* Set the number of screen updates to wait from the time glfwSwapBuffers was called before swapping */
    // 0 = no waiting for rendering the next frame
    // 1 = draw 1 image for each frames displayed on the screen (60Hz monitor = 60fps)
    // 2 = draw 1 image every 2 frames displayed on the screen (60hz monitor = 30 draw/s = 30fps)
    // 4 = draw 1 image every 4 frames displayed on the screen (60Hz monitor = 15 draw/s = 15fps)
    // etc ...
    glfwSwapInterval(2);

    return app;
}

void GLFWApplication::Terminate()
{
    static GLFWApplication* app = GLFWApplication::getInstance();
    VisualManager::Clean();

    if (!app->windowHandle) {
        glfwDestroyWindow(app->windowHandle);
        app->setWindow(nullptr);
    }

    glfwTerminate();
}

void GLFWApplication::FramebufferSizeCallback(GLFWwindow*, int width, int height)
{
    GLFWApplication::ScreenWidth = (unsigned int) width;
    GLFWApplication::ScreenHeight = (unsigned int) height;
}

void GLFWApplication::MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->mouseButtonCallback(handle, button, action, mods);
    }
}

void GLFWApplication::CursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->cursorPosCallback(handle, xpos, ypos);
    }
}

void GLFWApplication::ScrollCallback(GLFWwindow* handle, double xoffset, double yoffset)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->scrollCallback(handle, xoffset, yoffset);
    }
}

void GLFWApplication::KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->keyCallback(handle, key, scancode, action, mods);
    }
}

GLFWApplication::GLFWApplication() : Application(),
    windowHandle(nullptr),
    m_selectable(nullptr),
    m_scene(nullptr),
    m_viewer(nullptr),
    m_interface(nullptr)
{
    OurInstance = this;

    // create scene
    this->m_scene = new SceneGraph();
    // create viewer
    this->m_viewer = new Viewer(this->m_scene);
    // create interface
    this->m_interface = new GLFWApplicationEvents();
}

GLFWApplication::~GLFWApplication()
{
    delete m_selectable;
    m_selectable = nullptr;

    delete m_scene;
    m_scene = nullptr;

    delete m_viewer;
    m_viewer = nullptr;

    delete m_interface;
    m_interface = nullptr;
}

void GLFWApplication::init()
{

}

void GLFWApplication::loop()
{
    if (this->windowHandle == nullptr) {
        msg_error("App") << "Can't loop, set window first";
        return;
    }

//    double lastTime = glfwGetTime();
//    unsigned int nbFrames = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(this->windowHandle))
    {
//        // Measure speed
//        double currentTime = glfwGetTime();
//        nbFrames++;
//        /* If last print was more than 1 sec ago */
//        if (currentTime - lastTime >= 1.0)
//        {
//            msg_info("App") << 1000.0 / double(nbFrames) << " ms/frame";
//            nbFrames = 0;
//            lastTime += 1.0;
//        }

        /* Call to drawing function */
        this->m_viewer->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(this->windowHandle);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

GLFWwindow* GLFWApplication::getWindow() const
{
    return this->windowHandle;
}

void GLFWApplication::setWindow(GLFWwindow* newHandle)
{
    GLFWwindow* oldHandle = this->windowHandle;

    /* Remove callbacks set to the old handle */
    if (oldHandle != nullptr) {
        glfwSetFramebufferSizeCallback(oldHandle, nullptr);
        glfwSetMouseButtonCallback(oldHandle, nullptr);
        glfwSetCursorPosCallback(oldHandle, nullptr);
        glfwSetScrollCallback(oldHandle, nullptr);
        glfwSetKeyCallback(oldHandle, nullptr);
    }

    this->windowHandle = newHandle;

    /* Add callbacks to the new handle */
    if (newHandle != nullptr) {
        glfwSetFramebufferSizeCallback(newHandle, GLFWApplication::FramebufferSizeCallback);
        glfwSetMouseButtonCallback(newHandle, GLFWApplication::MouseButtonCallback);
        glfwSetCursorPosCallback(newHandle, GLFWApplication::CursorPosCallback);
        glfwSetScrollCallback(newHandle, GLFWApplication::ScrollCallback);
        glfwSetKeyCallback(newHandle, GLFWApplication::KeyCallback);
    }
}

Selectable* GLFWApplication::selected() const
{
    return this->m_selectable;
}

void GLFWApplication::setSelected(Selectable* selectable)
{
    if (this->m_selectable != nullptr) {
        delete m_selectable;
        this->m_selectable = nullptr;
    }

    this->m_selectable = selectable;
}

SceneGraph* GLFWApplication::getScene()
{
    return this->m_scene;
}

Viewer* GLFWApplication::getViewer()
{
    return this->m_viewer;
}

Interface* GLFWApplication::getInterface() const
{
    return this->m_interface;
}

void GLFWApplication::setInterface(Interface* interface)
{
    this->m_interface = interface;
}
