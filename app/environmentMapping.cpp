
#include <helper/FileRepository.h>
#include <glfw/GLFWApplication.h>
#include <glfw/GLFWCameraController.h>
#include <gltk.h>
#include <Mesh.h>
#include <helper/Message.h>
#include <graph/Node.h>
#include <statemachine/OpenGLAttribute.h>
#include <graph/SceneGraph.h>
#include <gui/SceneView.h>
#include <ShaderProgram.h>
#include <CubeMapTexture.h>
#include <graph/Visitor.h>
#include <VisualModel.h>

// Glfw
#include <GLFW/glfw3.h>

// Standard Library
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <string>

using namespace gl;
using namespace gl::helper;

static GLFWApplication* app = nullptr;
static std::shared_ptr<SceneGraph> scene(new SceneGraph());

using ShaderProgramType = GLTK::ShaderProgramType;

void createScene(Node* rootNode)
{
    Node* childNode;

    CubeMapTexture::SPtr cubeMapTexture(new CubeMapTexture());
    cubeMapTexture->load("textures/cubemap1.jpg");

    ////////////////////////////////////////

    childNode = rootNode->addChild();

    ShaderProgram::SPtr basicTexturingShader( ShaderProgram::Create(ShaderProgramType::EnvironmentMapping) );
    childNode->setShaderProgram(basicTexturingShader);

    basicTexturingShader->addDataTexture("cubeMap", cubeMapTexture.get());

    VisualModel::SPtr board(new VisualModel("mesh/Armadillo_simplified.obj"));
    childNode->addVisual(board);

    ////////////////////////////////////////

    childNode = rootNode->addChild();

    ShaderProgram::SPtr cubeMapShader( ShaderProgram::Create(ShaderProgramType::CubeMap) );
    childNode->setShaderProgram(cubeMapShader);

    cubeMapShader->addDataCubeMapTexture("cubeMap", cubeMapTexture.get());

    VisualModel::SPtr cube(new VisualModel("mesh/cube.obj"));
    childNode->addVisual(cube);
}

void fitView(SceneView* sceneView)
{
    if(!sceneView)
        return;

    SceneGraph* scene = sceneView->scene();
    Camera* camera = sceneView->camera();

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


void initGL();
void initGLTK();
void displayCallback();
void errorCallback [[noreturn]] (int error, const char* description);

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

void initGLTK()
{
    std::map<std::string, std::string> iniFileValues = GLTK::getMapFromIniFile("../etc/config.ini");

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

    createScene(scene->root());

    std::shared_ptr<SceneView> sceneView(new SceneView());

    int width = static_cast<int>(GLFWApplication::ScreenWidth);
    int height = static_cast<int>(GLFWApplication::ScreenHeight);
    Rect rect(0,0,width,height);
    std::shared_ptr<Controller> controller(new GLFWCameraController(sceneView));

    sceneView->setRect(rect);
    sceneView->setScene(scene);
    sceneView->setInterface(controller);

    fitView(sceneView.get());

    app->addSceneView(sceneView);

    Light light;
    light.setColor(glm::vec3(1,0,0));
    light.setDirection(glm::vec3(-1,-1,-1));

    sceneView->setLight(light);
}

void errorCallback(int, const char* description)
{
    // Throw an error
    throw std::runtime_error(description);
}
