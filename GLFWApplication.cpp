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

}

void GLFWApplication::KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{

}

GLFWApplication::GLFWApplication() : Application(),
    windowHandle(0),
    m_interface(0),
    m_mesh(0),
    m_camera(Camera::Perspective)
{

}

GLFWApplication::~GLFWApplication()
{
    delete this->m_mesh;
    this->m_mesh = nullptr;
    delete this->m_interface;
    this->m_interface = nullptr;
}

void GLFWApplication::init()
{
    typedef Shader::ShaderType ShaderType;

    // Specifies background color
    //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Specifies how polygons are rendered
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

    // interface
    this->m_interface = new GLFWApplicationEvents();

    // mesh
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/cube.obj");
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/dragon_low.obj");
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/Armadillo_simplified.obj");
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/sphere.obj");
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/pion.stl");
//    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/teapot.obj");
    this->m_mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/models/narrowarrow.obj");

    if (!this->m_mesh)
        return;

    // Shader program
    Program* program = this->addProgram();
//    program->addShaderProgram(ShaderProgram::Basic);
    program->addShaderProgram(ShaderProgram::FlatShading);
//    program->addShaderProgram(ShaderProgram::GouraudShading);
//    program->addShaderProgram(ShaderProgram::PhongShading);
//    program->addShaderProgram(ShaderProgram::Normal);
//    program->addShaderProgram(ShaderProgram::Frame);
//    program->setPolygonMode(Program::PolygonMode::POINT);

//    Program* program1 = this->addProgram();
//    program1->addShaderProgram(ShaderProgram::Frame);
//    program1->setPolygonMode(Program::PolygonMode::FILL);

    /* Camera specification */
    glm::vec3 min;
    glm::vec3 max;
    this->m_mesh->getBbox(min, max);

    float diagonal = glm::length(max - min);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::vec3(1,0,0) * diagonal);
    glm::vec3 up(0,0,1);
    this->m_camera.lookAt(eye, target, up);

//    msg_info("a") << target;
//    msg_info("b") << up;

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.2f * diagonal;
    float zFar = 2.0f * diagonal;
    this->m_camera.perspective(fovy, aspect, zNear, zFar);
}

void GLFWApplication::loop()
{
    double lastTime = glfwGetTime();
    unsigned int nbFrames = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowHandle))
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

    const Program* program = this->getProgram(0);
    program->draw();

//    const Program* program1 = this->getProgram(1);
//    program1->draw();

//    GLuint nbPixelsQuery;
//    int nbPixel = -1;

//    glGenQueries(1, &nbPixelsQuery);
//    glBeginQuery(GL_SAMPLES_PASSED, nbPixelsQuery);

//    this->m_mesh->draw();

//    glEndQuery(GL_SAMPLES_PASSED);
//    glGetQueryObjectiv(nbPixelsQuery, GL_QUERY_RESULT, &nbPixel);
//    glDeleteQueries(1, &nbPixelsQuery);

//    msg_info("Draw") << nbPixel << " passed";


    // draw here
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glLineWidth(1);
//    this->m_mesh->draw();
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
    // don't use this function (memory leaks)
    this->m_interface = newInterface;
}

Camera* GLFWApplication::getCamera()
{
    return &(this->m_camera);
}
