
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <GLFWApplicationEvents.h>
#include <Helper.h>
#include <Mesh.h>
#include <Message.h>
#include <Node.h>
#include <Rendered.h>
#include <Scene.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Visitor.h>
#include <VisualModel.h>

// Glfw
#include <GLFW/glfw3.h>

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <string>

using namespace gl;
using namespace gl::helper;

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    Node* childNode;

    CubeMapTexture* cubeMapTexture = new CubeMapTexture();
    cubeMapTexture->load("textures/cubemap1.jpg");

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* basicTexturingShader = helper::CreateShaderProgram(ShaderProgram::EnvironmentMapping);
    childNode->setShaderProgram(basicTexturingShader);

    basicTexturingShader->addData<Texture>("cubeMap", *cubeMapTexture);

    VisualModel* board = new VisualModel("mesh/Armadillo_simplified.obj");
    childNode->addVisual(board);

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* cubeMapShader = helper::CreateShaderProgram(ShaderProgram::CubeMap);
    childNode->setShaderProgram(cubeMapShader);

    cubeMapShader->addData<CubeMapTexture>("cubeMap", *cubeMapTexture);

//    cubeMapShader->set(OpenGLState::DepthMask, GL_FALSE);
//    cubeMapShader->set(OpenGLState::DepthFunc, GL_LEQUAL);
//    cubeMapShader->set(OpenGLState::CullFace, GL_FALSE);

    VisualModel* cube = new VisualModel("mesh/cube.obj");
    childNode->addVisual(cube);

    return scene;
}

void fitView(SceneGraph* scene, Camera* camera)
{
    glm::vec3 min;
    glm::vec3 max;
    scene->getBB(min, max);

    float diagonal = glm::length(max - min);
    glm::vec3 direction(-1,-1,-1);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::normalize(direction) * diagonal);
    glm::vec3 up(0,0,1);
    camera->lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.02f * diagonal;
    float zFar = 2.0f * diagonal;
    camera->perspective(fovy, aspect, zNear, zFar);
}


static GLFWApplication* app = nullptr;
static GLFWApplicationEvents* interface = nullptr;
static Rendered renderer;

void initGL();
void initGLTK();
void displayCallback();
void errorCallback(int error, const char* description);


int main()
{
    int return_code = EXIT_SUCCESS;

    /* Set an error callback */
    glfwSetErrorCallback(errorCallback);

    /* Create a window and its OpenGL context */
    app = GLFWApplication::CreateWindow(1280, 960);

    if (app == nullptr)
        return -1;

    try
    {
        // Initialise OpenGL
        initGL();

        // Initialise GLTK
        initGLTK();

        // Throws the main loop
        app->loop();
    }
    // Catch exception if any
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return_code = EXIT_FAILURE;
    }

    /* Close the window and shut GLFW if needed */
    GLFWApplication::Terminate();

    // Return an exit code
    return return_code;
}

void initGL()
{
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

    int glMajor;
    int glMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);

    msg_info("OpenGL") << "Congrat's ! You're running OpenGL " << glMajor << "." << glMinor;
}

void initGLTK()
{
    std::map<std::string, std::string> iniFileValues = getMapFromIniFile("../etc/config.ini");

    if (iniFileValues.find("SHARE_DIR") != iniFileValues.end()) {
        std::string ini_directories[4] = {
            iniFileValues["SHARE_DIR"],
            iniFileValues["MESHES_DIR"],
            iniFileValues["SHADERS_DIR"],
            iniFileValues["TEXTURES_DIR"]
        };
        for (std::string ini_dir : ini_directories) {
            DataRepository.addFirstPath(ini_dir);
        }
    } else {
        msg_warning("FileRepository") << "No share/ directory added";
    }

    renderer.scene = createScene();
    renderer.camera = new Camera();

    fitView(renderer.scene, renderer.camera);

    interface = new GLFWApplicationEvents(renderer.camera);
    app->setInterface(interface);

    app->setDrawCallBack(displayCallback);
}

void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.draw();
}

void errorCallback(int, const char* description)
{
    // Throw an error
    throw (description);
}
