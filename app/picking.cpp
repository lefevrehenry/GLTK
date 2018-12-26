
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

static Node* selectedNode = nullptr;

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    Node* childNode;

    std::string folder = "low_res";
    std::string extension = ".obj";

    Material mat1 = Material::Obsidian();
    Material mat2 = Material::Gold();
    Material mat3 = Material::Ruby();
    Material mat4 = Material::Bronze();
    Material mat5 = Material::Copper();
    Material mat6 = Material::Jade();

    VisualModel* pawn   = new VisualModel("mesh/" + folder + "/pion" + extension, mat1);
    VisualModel* rook   = new VisualModel("mesh/" + folder + "/tour" + extension, mat2);
    VisualModel* knight = new VisualModel("mesh/" + folder + "/cavalier" + extension, mat3);
    VisualModel* bishop = new VisualModel("mesh/" + folder + "/fou" + extension, mat4);
    VisualModel* queen  = new VisualModel("mesh/" + folder + "/reine" + extension, mat5);
    VisualModel* king   = new VisualModel("mesh/" + folder + "/roi" + extension, mat6);

    VisualModel* visualModels[6] = {pawn, rook, knight, bishop, queen, king};

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* phongShadingShader = helper::CreateShaderProgram(ShaderProgram::PhongShading);
    childNode->setShaderProgram(phongShadingShader);

    for (unsigned int i = 0; i < 6; ++i) {
        VisualModel* vm = visualModels[i];
        vm->transform().translate(25*i, 0, 0);
        childNode->addVisual(vm);
    }

    ////////////////////////////////////////

    childNode = root->addChild();

    ShaderProgram* highlightShader = helper::CreateShaderProgram(ShaderProgram::Normal);
    childNode->setShaderProgram(highlightShader);

    selectedNode = childNode;

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

void visualModelChanged(const VisualModel* visualModel, glm::vec4)
{
    selectedNode->removeVisual(0);

    if (visualModel != nullptr)
        selectedNode->addVisual(visualModel);
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

    InterfacePicking* interface = new InterfacePicking(renderer.scene, renderer.camera);
    interface->setCallback(visualModelChanged);
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
