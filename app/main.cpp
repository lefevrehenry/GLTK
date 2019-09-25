
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <GLFWApplicationEvents.h>
#include <Helper.h>
#include <Light.h>
#include <Mesh.h>
#include <Message.h>
#include <Node.h>
#include <SceneGraph.h>
#include <SceneView.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Visitor.h>
#include <VisualModel.h>
#include <VisualManager.h>

// Glm
#include <glm/gtx/transform.hpp>

// Glfw
#include <GLFW/glfw3.h>

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <chrono>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace gl;
using namespace gl::helper;

static GLFWApplication* app = nullptr;
static GLFWApplicationEvents* interface = nullptr;
static std::shared_ptr<SceneGraph> scene;
static VisualModel* vm = nullptr;

void addPiece(Node* node, Mesh* mesh, Material material, int i, int j)
{
    VisualModel* visualModel = new VisualModel(mesh, material);
    visualModel->transform().translate(-12.5f - (3 * 25) + (i * 25), -12.5f - (3 * 25) + (j * 25), 0);
    node->addVisual(visualModel);
}

void addMatCapShader(Node* node, std::string filename) {
    Texture* matcapTexture = new Texture2D();
    matcapTexture->load(filename);

    ShaderProgram* shaderProgram = ShaderProgram::Create(ShaderProgram::MatCap);
    shaderProgram->addData<Texture>("matcap", *matcapTexture);

    node->setShaderProgram(shaderProgram);
}

void createChessboard(Node* node)
{
    std::string folder = "low_res";
    std::string extension = ".obj";

    Mesh* pawn = Mesh::FromFile("mesh/" + folder + "/pion" + extension);
    Mesh* rook = Mesh::FromFile("mesh/" + folder + "/tour" + extension);
    Mesh* knight = Mesh::FromFile("mesh/" + folder + "/cavalier" + extension);
    Mesh* bishop = Mesh::FromFile("mesh/" + folder + "/fou" + extension);
    Mesh* queen = Mesh::FromFile("mesh/" + folder + "/reine" + extension);
    Mesh* king = Mesh::FromFile("mesh/" + folder + "/roi" + extension);

    Texture* boardColorTex = new Texture2D();
    boardColorTex->load("textures/chessboard2.jpg");

    ShaderProgram* shaderProgram = ShaderProgram::Create(ShaderProgram::BasicTexturing);
    shaderProgram->addData<Texture>("colorMap", *boardColorTex);

    VisualModel* board = new VisualModel("mesh/flatQuad.obj");
    float s = 118.5;
    board->transform().scale(s,s,s);

    node->setShaderProgram( shaderProgram );
    node->addVisual(board);

    // White Set

    Node* nodeWhite = node->addChild();
    addMatCapShader(nodeWhite, "textures/m8.jpg");

//    ShaderProgram* sp = ShaderProgram::Create(ShaderProgram::PhongShading);
//    nodeWhite->setShaderProgram(sp);

    Material materialWhite = Material::Brass();

    addPiece(nodeWhite, king,   materialWhite, 4, 0);
    addPiece(nodeWhite, queen,  materialWhite, 3, 0);
    addPiece(nodeWhite, bishop, materialWhite, 2, 0);
    addPiece(nodeWhite, bishop, materialWhite, 5, 0);
    addPiece(nodeWhite, knight, materialWhite, 1, 0);
    addPiece(nodeWhite, knight, materialWhite, 6, 0);
    addPiece(nodeWhite, rook,   materialWhite, 0, 0);
    addPiece(nodeWhite, rook,   materialWhite, 7, 0);
    addPiece(nodeWhite, pawn,   materialWhite, 0, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 1, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 2, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 3, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 4, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 5, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 6, 1);
    addPiece(nodeWhite, pawn,   materialWhite, 7, 1);

    // Black Set

    Node* nodeBlack = node->addChild();
    addMatCapShader(nodeBlack, "textures/metal.jpg");

//    nodeBlack->setShaderProgram(sp);

    Material materialBlack = Material::Silver();

    addPiece(nodeBlack, king,   materialBlack, 4, 7);
    addPiece(nodeBlack, queen,  materialBlack, 3, 7);
    addPiece(nodeBlack, bishop, materialBlack, 2, 7);
    addPiece(nodeBlack, bishop, materialBlack, 5, 7);
    addPiece(nodeBlack, knight, materialBlack, 1, 7);
    addPiece(nodeBlack, knight, materialBlack, 6, 7);
    addPiece(nodeBlack, rook,   materialBlack, 0, 7);
    addPiece(nodeBlack, rook,   materialBlack, 7, 7);
    addPiece(nodeBlack, pawn,   materialBlack, 0, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 1, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 2, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 3, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 4, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 5, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 6, 6);
    addPiece(nodeBlack, pawn,   materialBlack, 7, 6);
}

void createScene(Node* rootNode)
{
    vm = new VisualModel("dragon_low.obj", Material::Emerald());
    rootNode->addVisual(vm);

    Light light;
    light.setDirection(glm::vec3(-1,-1,-1));

    VisualManager::UpdateUniformBufferLight(light);

    ShaderProgram* shaderProgram = ShaderProgram::Create(ShaderProgram::PhongShading);
    rootNode->setShaderProgram(shaderProgram);

//    Node* node1 = root->addChild();
//    node1->setShaderProgram(ShaderProgram::Create(ShaderProgram::PhongShading));

//    VisualModel* frame = new VisualModel("frame.obj", Material::Gold());
//    node1->addVisual(frame);

//    Node* node1 = root->addChild();
//    node1->addVisual(vm);
//    ShaderProgram* hightlightShading = ShaderProgram::Create(ShaderProgram::HighLight);
//    node1->setShaderProgram(hightlightShading);

//    Node* node2 = root->addChild();
//    node2->addVisual(vm);
//    ShaderProgram* normalShading = ShaderProgram::Create(ShaderProgram::Normal);
//    node2->setShaderProgram(normalShading);

    //createChessboard(root);
}

void fitView(SceneView* sceneView)
{
    std::shared_ptr<SceneGraph> scene(sceneView->scene());
    std::shared_ptr<Camera> camera(sceneView->camera());

    if(!scene || !camera)
        return;

    glm::vec3 min;
    glm::vec3 max;
    scene->getBB(min, max);

    float diagonal = glm::length(max - min);
    glm::vec3 direction(0,-1,0);

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
void errorCallback [[ noreturn ]] (int, const char* description);

static bool stopThread = false;
static glm::vec3 target_position(0,0,0);
static unsigned int duration = 0;
// number of frame per second
static unsigned short fps = 20;

void callback()
{
    // time waiting between each frame to achieve desired fps
    double frameRate = 1000.0 / fps;

    // number of frames counted this second
    long int frameCount = 0;

    // accumulate elapsed time over multiple frames
    double totalElapsedTime = 0;

    // the actual calculated framerate reported
    long int reportedFramerate = 0;

    while(!stopThread)
    {
        // time the frame began
        double frameStart = glfwGetTime();

        if (vm != nullptr) {
            Transform& tr = vm->transform();
//            float angle = ((90.f / 180.f) * glm::pi<float>()) / fps;
//            glm::vec3 axis(0,1,0);
//            glm::quat q = glm::angleAxis(angle,axis);
//            tr.rotate(q);

//            if (duration > 0) {
//                float d = duration;
//                glm::vec3& position = tr.m_translation;
//                position = (position * (d-1) + target_position) / d;
//                duration -= 1;
//                tr.m_isDirty = true;
//            }

//            tr.translate(0.f,0.01f,0.f);
        }

        // time elapsed during one frame
        double elapsedTime = glfwGetTime() - frameStart;

        if (elapsedTime < frameRate) {
            long int t = long(frameRate - elapsedTime);
            std::chrono::milliseconds dt = std::chrono::milliseconds(t);
            std::this_thread::sleep_for(dt);
        }

        frameCount += 1;
        totalElapsedTime += glfwGetTime() - frameStart;

        if (totalElapsedTime > 1) {
            reportedFramerate = long(frameCount / totalElapsedTime);
            //msg_info("Thread") << "fps: " << reportedFramerate;
            frameCount = 0;
            totalElapsedTime = 0;
        }
    }

    msg_info("Thread") << "Terminate";
}

int main()
{
    int return_code = EXIT_SUCCESS;

    /* Set an error callback */
    glfwSetErrorCallback(errorCallback);

    /* Create a window and its OpenGL context */
    app = GLFWApplication::CreateWindow(1280, 960);

    if (app == nullptr)
        return -1;

//    std::thread t1(callback);

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

//    stopThread = true;
//    t1.join();

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

    SceneView* sceneView = app->createSceneView();

    scene.reset(new SceneGraph());
    createScene(scene->root());

    sceneView->setScene(scene);
    sceneView->setInterface(CameraController::CameraType::ArcBall);

    fitView(sceneView);
}

void errorCallback(int, const char* description)
{
    // Throw an error
    throw std::runtime_error(description);
}
