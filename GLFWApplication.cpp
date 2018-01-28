#include "GLFWApplication.h"

#include "Camera.h"
#include "GLFWApplicationEvents.h"
#include "Helper.h"
#include "Mesh.h"
#include "Message.h"
#include "Shader.h"

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

void GLFWApplication::mouseInput(GLFWwindow* handle, int button, int action, int mods)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->mouseButtonCallback(handle, button, action, mods);
    }
}

void GLFWApplication::mousePos(GLFWwindow* handle, double xpos, double ypos)
{
    GLFWApplication* app = GLFWApplication::getInstance();

    if (app->getInterface() != nullptr) {
        app->getInterface()->cursorPosCallback(handle, xpos, ypos);
    }
}

void GLFWApplication::mouseScroll(GLFWwindow* handle, double xoffset, double yoffset)
{

}

void GLFWApplication::keyboardInput(GLFWwindow* handle, int key, int scancode, int action, int mods)
{

}

GLFWApplication::GLFWApplication() : Application(),
    windowHandle(0),
    m_interface(0),
    m_mesh(0),
    m_program(),
    m_program_normal(),
    m_camera(Camera::Perspective)
{
    init();
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

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // Specifies how polygons are rendered
//    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Enable eliminaton of hidden faces
    glEnable(GL_CULL_FACE);
    // Specifies whether front or back facing facets are candidates for culling
    glCullFace(GL_BACK);
    // Specifies the orientation of front-facing polygons
    glFrontFace(GL_CCW);

    // interface
    this->m_interface = new GLFWApplicationEvents();

    // mesh
//    this->m_mesh = Mesh::fromObj("/home/henry/dev/QtProject/OpenGL/models/cube.obj");
    this->m_mesh = Mesh::fromObj("/home/henry/dev/QtProject/OpenGL/models/dragon_low.obj");
//    this->m_mesh = Mesh::fromObj("/home/henry/dev/QtProject/OpenGL/models/Armadillo_simplified.obj");

    if (!this->m_mesh)
        return;

    // shader program
    std::string vs;
    std::string gs;
    std::string fs;

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    // Basic program
    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.vs", vs);
    vertexShader.compileSourceCode(vs);
    m_program.addShader(vertexShader);

    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.gs", gs);
//    geometryShader.compileSourceCode(gs);
//    m_program.addShader(geometryShader);

    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.fs", fs);
    fragmentShader.compileSourceCode(fs);
    m_program.addShader(fragmentShader);

    m_program.link();

    if (!m_program.isLinked())
        return;

    // Normal program
    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.vs", vs);
    vertexShader.compileSourceCode(vs);
    m_program_normal.addShader(vertexShader);

    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.gs", gs);
    geometryShader.compileSourceCode(gs);
    m_program_normal.addShader(geometryShader);

    gl::helper::getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.fs", fs);
    fragmentShader.compileSourceCode(fs);
    m_program_normal.addShader(fragmentShader);

    m_program_normal.link();

    if (!m_program_normal.isLinked())
        return;

    /* Camera specification */
    glm::vec3 min;
    glm::vec3 max;
    this->m_mesh->getBbox(min, max);

    float diagonal = glm::length(max - min);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::vec3(0,0,1) * diagonal);
    glm::vec3 up(0,1,0);
    this->m_camera.lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.2f * diagonal;
    float zFar = 2.0f * diagonal;
    this->m_camera.perspective(fovy, aspect, zNear, zFar);

    /* Set the number of screen updates to wait from the time glfwSwapBuffers was called before swapping */
    // 0 = no waiting for rendering the next frame
    // 1 = draw 1 image for each frames displayed on the screen (60Hz monitor = 60fps)
    // 2 = draw 1 image every 2 frames displayed on the screen (60hz monitor = 30 draw/s = 30fps)
    // 4 = draw 1 image every 4 frames displayed on the screen (60Hz monitor = 15 draw/s = 15fps)
    // etc ...
    glfwSwapInterval(2);
}

#include "Helper.h"

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

    glUseProgram(m_program.getProgramID());

    glm::mat4 model = glm::mat4();
    glm::mat4 view = this->m_camera.view();
    glm::mat4 proj = this->m_camera.projection();

    GLint viewProjLocation = glGetUniformLocation(m_program.getProgramID(), "mvp");
    glUniformMatrix4fv(viewProjLocation, 1, GL_FALSE, glm::value_ptr(proj * view * model));

    glm::vec3 color(1.0, 1.0, 0.0);
    GLint colorLocation = glGetUniformLocation(m_program.getProgramID(), "color");
    glUniform3fv(colorLocation, 1, glm::value_ptr(color));

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->m_mesh->draw();

    glUseProgram(m_program_normal.getProgramID());

    viewProjLocation = glGetUniformLocation(m_program_normal.getProgramID(), "mvp");
    glUniformMatrix4fv(viewProjLocation, 1, GL_FALSE, glm::value_ptr(proj * view * model));

    GLint normalMatLocation = glGetUniformLocation(m_program_normal.getProgramID(), "normal_mat");
    glUniformMatrix3fv(normalMatLocation, 1, GL_FALSE, glm::value_ptr(this->m_camera.normal()));

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//    this->m_mesh->drawNormal();

//    color = glm::vec3(0.0, 0.0, 0.0);
//    glUniform3fv(colorLocation, 1, glm::value_ptr(color));

    // draw here
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glLineWidth(1);
//    this->m_mesh->draw();

    glUseProgram(0);
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
        glfwSetMouseButtonCallback(oldHandle, nullptr);
        glfwSetCursorPosCallback(oldHandle, nullptr);
        glfwSetScrollCallback(oldHandle, nullptr);
        glfwSetKeyCallback(oldHandle, nullptr);
    }

    this->windowHandle = newHandle;

    /* Add callbacks to the new handle */
    if (newHandle != nullptr) {
        glfwSetMouseButtonCallback(newHandle, GLFWApplication::mouseInput);
        glfwSetCursorPosCallback(newHandle, GLFWApplication::mousePos);
        glfwSetScrollCallback(newHandle, GLFWApplication::mouseScroll);
        glfwSetKeyCallback(newHandle, GLFWApplication::keyboardInput);
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
