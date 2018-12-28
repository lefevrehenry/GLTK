
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

    Texture2D* textureColor = new Texture2D();
    textureColor->load("textures/Brick_Wall_color.jpg");

    Texture2D* textureNormal = new Texture2D();
    textureNormal->load("textures/Brick_Wall_normal_smooth.jpg");

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* basicTexturingShader = helper::CreateShaderProgram(ShaderProgram::NormalMapping);
    childNode->setShaderProgram(basicTexturingShader);

    basicTexturingShader->addData<Texture>("colorMap", *textureColor);
    basicTexturingShader->addData<Texture>("normalMap", *textureNormal);
//    basicTexturingShader->set(OpenGLState::CullFace, GL_FALSE);

    VisualModel* board = new VisualModel("mesh/flatQuad.obj");
    childNode->addVisual(board);

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* tangentSpaceShader = helper::CreateShaderProgram(ShaderProgram::TangentSpace);
    tangentSpaceShader->addData<float>("scale", 0.5f);
    childNode->setShaderProgram(tangentSpaceShader);

    childNode->addVisual(board);

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

    Light light;
    light.setPosition(glm::vec3(0,0,0));
    light.setDirection(glm::vec3(0,0,-1));
    light.setColor(glm::vec3(1,1,1));

    VisualManager::UpdateUniformBufferLight(light);

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
