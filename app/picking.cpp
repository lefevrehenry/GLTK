
#include <misc/Camera.h>
#include <helper/FileRepository.h>
#include <glfw/GLFWApplication.h>
#include <glfw/GLFWPickingController.h>
#include <gltk.h>
#include <misc/Light.h>
#include <Mesh.h>
#include <helper/Message.h>
#include <graph/Node.h>
#include <graph/SceneGraph.h>
#include <gui/SceneView.h>
#include <ShaderProgram.h>
#include <VisualModel.h>
#include <graph/VisualModel.h>

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

static GLFWApplication* app = nullptr;
static std::shared_ptr<SceneGraph> scene(new SceneGraph());
static Node* selectedNode = nullptr;

using ShaderProgramType = GLTK::ShaderProgramType;

void createScene(Node* rootNode)
{
    Node* childNode;

    std::string folder = "low_res";
    std::string extension = ".obj";

    Material mat1 = Material::Obsidian();
    Material mat2 = Material::Gold();
    Material mat3 = Material::Ruby();
    Material mat4 = Material::Bronze();
    Material mat5 = Material::Copper();
    Material mat6 = Material::Jade();

    Mesh::SPtr   pawn(new Mesh("mesh/" + folder + "/pion" + extension));
    Mesh::SPtr   rook(new Mesh("mesh/" + folder + "/tour" + extension));
    Mesh::SPtr knight(new Mesh("mesh/" + folder + "/cavalier" + extension));
    Mesh::SPtr bishop(new Mesh("mesh/" + folder + "/fou" + extension));
    Mesh::SPtr  queen(new Mesh("mesh/" + folder + "/reine" + extension));
    Mesh::SPtr   king(new Mesh("mesh/" + folder + "/roi" + extension));

    Mesh::SPtr meshes[6] = {pawn, rook, knight, bishop, queen, king};
    Material materials[6] = {mat1, mat2, mat3, mat4, mat5, mat6};

    ////////////////////////////////////////

    childNode = rootNode->addChild();

    ShaderProgram::SPtr phongShadingShader( ShaderProgram::Create(ShaderProgramType::PhongShading) );
    childNode->setShaderProgram(phongShadingShader);

    for (unsigned int i = 0; i < 6; ++i) {
        Mesh::SPtr mesh = meshes[i];
        const Material& material = materials[i];
        VisualModel::SPtr vm(new VisualModel(mesh, material));
        vm->transform().translate(25*i, 0, 0);
        childNode->addVisual(vm);
    }

    ////////////////////////////////////////

    childNode = rootNode->addChild();

    ShaderProgram::SPtr highlightShader( ShaderProgram::Create(ShaderProgramType::Normal) );
    childNode->setShaderProgram(highlightShader);

    selectedNode = childNode;
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

void visualModelChanged(std::weak_ptr<const VisualModel> visualModel, glm::vec4)
{
    selectedNode->removeVisual(0);

    VisualModel::CSPtr vm = visualModel.lock();
    if (vm != nullptr)
        selectedNode->addVisual(vm);
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

    int width = static_cast<int>(Application::ScreenWidth);
    int height = static_cast<int>(Application::ScreenHeight);
    Rect rect(0,0,width,height);
    std::shared_ptr<GLFWPickingController> controller(new GLFWPickingController(sceneView));
    controller->setCallback(visualModelChanged);

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
    throw (description);
}
