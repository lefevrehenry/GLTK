#include "GLFWApplication.h"

#include "Camera.h"
#include "GLFWApplicationEvents.h"
#include "Helper.h"
#include "Mesh.h"
#include "Message.h"
#include "Program.h"
#include "Shader.h"
#include "ShaderProgram.h"

// OpenGL
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace gl;

GLFWApplication* GLFWApplication::getInstance()
{
    static GLFWApplication window;   // instantiated on first use only

    return &window;
}

GLFWApplication* GLFWApplication::CreateWindow()
{
    /* GLFW initialization */
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* windowHandle = glfwCreateWindow(640, 480, "OpenGL", nullptr, nullptr);

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

    static GLFWApplication* app = GLFWApplication::getInstance();
    app->setWindow(windowHandle);

    // Specifies background color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // Enable depth test
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

    if (!app->windowHandle) {
        glfwDestroyWindow(app->windowHandle);
        app->setWindow(nullptr);
    }

    glfwTerminate();
}

void GLFWApplication::FramebufferSizeCallback(GLFWwindow *handle, int width, int height)
{
    glViewport(0, 0, width, height);
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
    windowHandle(0),
    m_interface(0)
{
    // interface
    this->m_interface = new GLFWApplicationEvents();
}

GLFWApplication::~GLFWApplication()
{
    if (this->m_interface) {
        delete this->m_interface;
        this->m_interface = nullptr;
    }
}

void GLFWApplication::init()
{
    typedef Shader::ShaderType ShaderType;

    // mesh
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/cube.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/flatQuad.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/dragon_low.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/Armadillo_simplified.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/sphere.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/pion.stl");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/tour.stl");
    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/teapot.obj");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/monkey.off");
//    this->m_scene->addMesh("/home/henry/dev/QtProject/OpenGL/share/models/monkey_uv.obj");


    // Shader program
    Program* program = this->addProgram();
//    program->addShaderProgram(ShaderProgram::Basic);
//    program->addShaderProgram(ShaderProgram::FlatShading);
//    program->addShaderProgram(ShaderProgram::GouraudShading);
    program->addShaderProgram(ShaderProgram::PhongShading);
//    program->addShaderProgram(ShaderProgram::Normal);
//    program->addShaderProgram(ShaderProgram::Frame);
//    program->addShaderProgram(ShaderProgram::HighLight);
//    program->addShaderProgram(ShaderProgram::Texturing);
//    program->addShaderProgram(ShaderProgram::TangentSpace);

//    Program* program1 = this->addProgram();
//    program1->addShaderProgram(ShaderProgram::Frame);

    /* Camera specification */
    this->m_scene->fit();
}

void GLFWApplication::loop()
{
    if (this->windowHandle == nullptr) {
        msg_error("App") << "Can't loop, set window first";
        return;
    }

    double lastTime = glfwGetTime();
    unsigned int nbFrames = 0;

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
        this->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(this->windowHandle);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void GLFWApplication::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < getNbProgram(); ++i) {
        const Program* program = getProgram(i);
        program->draw();
    }

//    GLuint nbPixelsQuery;
//    int nbPixel = -1;

//    glGenQueries(1, &nbPixelsQuery);
//    glBeginQuery(GL_SAMPLES_PASSED, nbPixelsQuery);

//    this->m_mesh->draw();

//    glEndQuery(GL_SAMPLES_PASSED);
//    glGetQueryObjectiv(nbPixelsQuery, GL_QUERY_RESULT, &nbPixel);
//    glDeleteQueries(1, &nbPixelsQuery);

//    msg_info("Draw") << nbPixel << " passed";
}

GLFWwindow* GLFWApplication::getWindow() const
{
    return this->windowHandle;
}

void GLFWApplication::setWindow(GLFWwindow* newHandle)
{
    GLFWwindow* oldHandle = this->windowHandle;

    typedef void (*cursorPosCallback) (GLFWwindow*, double, double);

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

Interface* GLFWApplication::getInterface() const
{
    return this->m_interface;
}

void GLFWApplication::setInterface(Interface* newInterface)
{
    this->m_interface = newInterface;
}
