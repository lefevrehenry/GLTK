#include <gltk.h>

#include <Camera.h>
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <GLFWCameraController.h>
#include <Light.h>
#include <Material.h>
#include <Mesh.h>
#include <Message.h>
#include <Node.h>
#include <SceneGraph.h>
#include <SceneView.h>
#include <ShaderProgram.h>
#include <Texture2D.h>
#include <Visitor.h>
#include <VisualModel.h>
#include <Rect.h>
#include <PhongShaderProgram.h>
#include <MatCapShaderProgram.h>
#include <NormalShaderProgram.h>
#include <HighLightShaderProgram.h>

// Glm
#include <glm/gtx/transform.hpp>

// Glfw
#include <GLFW/glfw3.h>

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
static std::shared_ptr<SceneGraph> scene(new SceneGraph());

using ShaderProgramType = GLTK::ShaderProgramType;

void addPiece(Node* node, Mesh::SPtr mesh, Material material, int i, int j)
{
    VisualModel::SPtr visualModel(new VisualModel(mesh, material));
    visualModel->transform().translate(-12.5f - (3 * 25) + (i * 25), -12.5f - (3 * 25) + (j * 25), 0);
    node->addVisual(visualModel);
}

void addPhongShadingShader(Node* node) {
    ShaderProgram::SPtr sp(new PhongShaderProgram());
    node->setShaderProgram(sp);
}

void addMatCapShader(Node* node, const std::string& filename) {
    Texture::SPtr matcapTexture(new Texture2D());
    matcapTexture->load(filename);

    MatCapShaderProgram::SPtr sp(new MatCapShaderProgram());
    sp->setMatCapTexture(std::string(""));
    //sp->addData("matcap", matcapTexture.get());

    node->setShaderProgram(sp);
}

void createChessboard(Node* node)
{
    std::string folder = "low_res";
    std::string extension = ".obj";

    Mesh::SPtr   pawn(new Mesh("mesh/" + folder + "/pion" + extension));
    Mesh::SPtr   rook(new Mesh("mesh/" + folder + "/tour" + extension));
    Mesh::SPtr knight(new Mesh("mesh/" + folder + "/cavalier" + extension));
    Mesh::SPtr bishop(new Mesh("mesh/" + folder + "/fou" + extension));
    Mesh::SPtr  queen(new Mesh("mesh/" + folder + "/reine" + extension));
    Mesh::SPtr   king(new Mesh("mesh/" + folder + "/roi" + extension));

    // White Set

    Node* nodeWhite = node->addChild();
//    addPhongShadingShader(nodeWhite);
    addMatCapShader(nodeWhite, "textures/m8.jpg");

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
//    addPhongShadingShader(nodeBlack);
    addMatCapShader(nodeBlack, "textures/metal.jpg");

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

void createBoard(Node* node)
{
//    float s = 118.5;

//    Texture::SPtr boardColorTex(new Texture2D());
//    boardColorTex->load("textures/chessboard2.jpg");

//    ShaderProgram::SPtr shaderProgram( ShaderProgram::Create(ShaderProgramType::BasicTexturing) );
//    shaderProgram->addData("colorMap", boardColorTex.get());

//    VisualModel::SPtr board(new VisualModel("mesh/flatQuad.obj"));
//    board->transform().scale(s,s,s);

//    node->setShaderProgram(shaderProgram);
//    node->addVisual(board);
}

void createScene(Node* rootNode)
{
    VisualModel::SPtr visualModel;
    ShaderProgram::SPtr shaderProgram;

    // rootNode
    visualModel.reset(new VisualModel("mesh/dragon_low.obj", Material::Emerald()));
    rootNode->addVisual(visualModel);

    shaderProgram.reset( new PhongShaderProgram() );
    rootNode->setShaderProgram(shaderProgram);

    // node 1
    Node* node1 = rootNode->addChild();
    node1->addVisual(visualModel);

    shaderProgram.reset( new HighLightShaderProgram() );
    node1->setShaderProgram(shaderProgram);

    // node 2
    Node* node2 = rootNode->addChild();
    node2->addVisual(visualModel);

    NormalShaderProgram* nsp = new NormalShaderProgram();
    nsp->setNormalScale(.5f);
    nsp->setNormalColor(glm::vec3(1,1,1));

    shaderProgram.reset( nsp );
    node2->setShaderProgram(shaderProgram);

//    createBoard(rootNode);
//    createChessboard(rootNode);
}

void fitView(SceneView* sceneView)
{
    if(!sceneView)
        return;

    SceneGraph* scene = sceneView->scene();
    Camera* camera = sceneView->camera();

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


void initGLTK();
void errorCallback [[ noreturn ]] (int, const char* description);

//static bool stopThread = false;
//static glm::vec3 target_position(0,0,0);
//static unsigned int duration = 0;
// number of frame per second
//static unsigned short fps = 20;

//void callback()
//{
//    // time waiting between each frame to achieve desired fps
//    double frameRate = 1000.0 / fps;

//    // number of frames counted this second
//    long int frameCount = 0;

//    // accumulate elapsed time over multiple frames
//    double totalElapsedTime = 0;

//    // the actual calculated framerate reported
//    long int reportedFramerate = 0;

//    while(!stopThread)
//    {
//        // time the frame began
//        double frameStart = glfwGetTime();

//        if (vm != nullptr) {
////            Transform& tr = vm->transform();
////            float angle = ((90.f / 180.f) * glm::pi<float>()) / fps;
////            glm::vec3 axis(0,1,0);
////            glm::quat q = glm::angleAxis(angle,axis);
////            tr.rotate(q);

////            if (duration > 0) {
////                float d = duration;
////                glm::vec3& position = tr.m_translation;
////                position = (position * (d-1) + target_position) / d;
////                duration -= 1;
////                tr.m_isDirty = true;
////            }

////            tr.translate(0.f,0.01f,0.f);
//        }

//        // time elapsed during one frame
//        double elapsedTime = glfwGetTime() - frameStart;

//        if (elapsedTime < frameRate) {
//            long int t = long(frameRate - elapsedTime);
//            std::chrono::milliseconds dt = std::chrono::milliseconds(t);
//            std::this_thread::sleep_for(dt);
//        }

//        frameCount += 1;
//        totalElapsedTime += glfwGetTime() - frameStart;

//        if (totalElapsedTime > 1) {
//            reportedFramerate = long(frameCount / totalElapsedTime);
//            //msg_info("Thread") << "fps: " << reportedFramerate;
//            frameCount = 0;
//            totalElapsedTime = 0;
//        }
//    }

//    msg_info("Thread") << "Terminate";
//}

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

void initGLTK()
{
    std::map<std::string, std::string> iniFileValues = GLTK::GetMapFromIniFile("../etc/config.ini");

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
    DataRepository.addFirstPath("../share/");

    createScene(scene->root());

    std::shared_ptr<SceneView> sceneView(new SceneView());

    int width = static_cast<int>(Application::ScreenWidth);
    int height = static_cast<int>(Application::ScreenHeight);
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
