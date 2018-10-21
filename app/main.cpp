
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <Mesh.h>
#include <Message.h>
#include <Node.h>
#include <Scene.h>
#include <Viewport.h>
#include <Rendered.h>

#include "GLFWApplicationEvents.h"
#include <Helper.h>
#include <Program.h>
#include <ShaderProgram.h>
#include <VisualModel.h>
#include <VisualOption.h>
#include <Texture.h>
#include <Visitor.h>

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <map>
#include <string>

using namespace gl;
using namespace gl::helper;

void addPiece(Node* node, Mesh* mesh, Material material, int i, int j)
{
    VisualModel* visualModel = new VisualModel(mesh, material);
    visualModel->transform().translate(-12.5f - (3 * 25) + (i * 25), -12.5f - (3 * 25) + (j * 25), 0);
    node->addVisual(visualModel);
}

void addMatCapShader(Node* node, std::string filename) {
    typedef Shader::ShaderType ShaderType;

    ShaderProgram* shaderProgram = new ShaderProgram();

    std::string vs = "";
    std::string gs = "";
    std::string fs = "";

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    getStringFromQrcFile(":/shaders/matcap.vs", vs);
    getStringFromQrcFile(":/shaders/matcap.fs", fs);

    if (vs != "") {
        vertexShader.compileSourceCode(vs);
        shaderProgram->addShader(vertexShader);
    }

    if (gs != "") {
        geometryShader.compileSourceCode(gs);
        shaderProgram->addShader(geometryShader);
    }

    if (fs != "") {
        fragmentShader.compileSourceCode(fs);
        shaderProgram->addShader(fragmentShader);
    }

    shaderProgram->link();

    Texture* matcapTexture = new Texture();
    matcapTexture->load(filename);

    shaderProgram->addData<Texture>("matcap", *matcapTexture);
    shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
    shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

    node->setShaderProgram(shaderProgram);
}

void createChessboard(Node* node)
{
    std::string folder = "low_res";
    std::string extension = ".obj";

    Mesh* pawn = Mesh::FromFile("models/" + folder + "/pion" + extension);
    Mesh* rook = Mesh::FromFile("models/" + folder + "/tour" + extension);
    Mesh* knight = Mesh::FromFile("models/" + folder + "/cavalier" + extension);
    Mesh* bishop = Mesh::FromFile("models/" + folder + "/fou" + extension);
    Mesh* queen = Mesh::FromFile("models/" + folder + "/reine" + extension);
    Mesh* king = Mesh::FromFile("models/" + folder + "/roi" + extension);

    ShaderProgram* shaderProgram = helper::CreateShaderProgram(ShaderProgram::Deferred);
    VisualModel* board = new VisualModel("models/flatQuad.obj");
    float s = 118.5;
    board->transform().scale(s,s,s);

    node->setShaderProgram( shaderProgram );
    node->addVisual(board);

    // White Set

    Node* nodeWhite = node->addChild();
//    addMatCapShader(nodeWhite, "textures/m8.jpg");

//    ShaderProgram* sp = helper::CreateShaderProgram(ShaderProgram::PhongShading);
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
//    addMatCapShader(nodeBlack, "textures/metal.jpg");

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

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    createChessboard(root);

//    Node* node1 = root->addChild();

//    ShaderProgram* shaderProgram[2];

////    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::Basic);
//    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::PhongShading);
////    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::MatCap);
////    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::Frame);
////    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::Normal);
////    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::TangentSpace);
////    shaderProgram[2] = helper::CreateShaderProgram(ShaderProgram::HighLight);

//    node1->setShaderProgram(shaderProgram[0]);

//    VisualModel* visual1 = new VisualModel("models/tour.stl",  Material::Bronze());
////    VisualModel* visual1 = New VisualModel("models/Armadillo_simplified.obj",  Material::Gold());
////    VisualModel* visual1 = New VisualModel("models/dragon_low.obj",            Material::Obsidian());
////    VisualModel* visual1 = New VisualModel("models/reine.stl",            Material::Obsidian());
////    VisualModel* visual1 = New VisualModel("models/teapot.obj",            Material::Gold());
////    VisualModel* visual1 = New VisualModel("models/frame.obj",            Material::Gold());
////    VisualModel* visual2 = New VisualModel("models/arrow.obj");

//    // Node 1
//    node1->addVisual(visual1);

    return scene;
}

Camera fitCamera(SceneGraph* scene)
{
    BoundingBoxVisitor boundingBoxVisitor;

    Node* root = scene->root();
    root->executeVisitor(&boundingBoxVisitor);

    glm::vec3 min = boundingBoxVisitor.getMin();
    glm::vec3 max = boundingBoxVisitor.getMax();

    float diagonal = glm::length(max - min);

    Camera camera;

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::vec3(0,0,-1) * diagonal);
    glm::vec3 up(0,1,0);
    camera.lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.02f * diagonal;
    float zFar = 2.0f * diagonal;
    camera.perspective(fovy, aspect, zNear, zFar);

    return camera;
}

SceneGraph* createVaoScene(Texture* textureColor)
{
    SceneGraph* scene = new SceneGraph();
    Node* root = scene->root();

    VisualModel* vaoQuad = new VisualModel("models/vaoQuad.obj");
    root->addVisual(vaoQuad);

    ShaderProgram* shaderProgram = helper::CreateShaderProgram(ShaderProgram::VaoQuad);
    shaderProgram->addData<Texture>("textureColor", *textureColor);
    root->setShaderProgram(shaderProgram);

    return scene;
}

int main()
{
    GLFWApplication::ScreenWidth = 1280;
    GLFWApplication::ScreenHeight = 960;

    /* Create a window and its OpenGL context */
    GLFWApplication* app = GLFWApplication::CreateWindow();

    if (!app)
        return -1;

    int glMajor;
    int glMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);

    msg_info("OpenGL") << "Congrat's ! You're running OpenGL " << glMajor << "." << glMinor;


    std::map<std::string, std::string> iniFileValues = getMapFromIniFile("../etc/config.ini");

    if (iniFileValues.find("SHARE_DIR") != iniFileValues.end()) {
        std::string shareDir = iniFileValues["SHARE_DIR"];
        DataRepository.addFirstPath(shareDir);
    } else {
        msg_warning("FileRepository") << "No share/ directory added";
    }

    SceneGraph* scene = createScene();
    Camera camera = fitCamera(scene);
    Viewport viewport(0,0,1,1);
    DrawVisitor visitor;

    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;
    Framebuffer fbo(width, height);
    fbo.attachTexture();
    fbo.attachTexture();
    fbo.attachTexture();
    fbo.attachDepthTexture();

    Rendered fboRender;
    fboRender.scene = scene;
    fboRender.camera = &camera;
    fboRender.viewport = &viewport;
    fboRender.framebuffer = &fbo;
    fboRender.visitor = &visitor;


    SceneGraph* vaoScene1 = createVaoScene(fbo.renderTexture(0));
    SceneGraph* vaoScene2 = createVaoScene(fbo.renderTexture(1));
    SceneGraph* vaoScene3 = createVaoScene(fbo.renderTexture(2));

    Viewport viewport_bl( 0, 0,.5,.5);
    Viewport viewport_br(.5, 0,.5,.5);
    Viewport viewport_tl( 0,.5,.5,.5);
    Viewport viewport_tr(.5,.5,.5,.5);

    Rendered defaultRender1;
    defaultRender1.scene = vaoScene1;
    defaultRender1.camera = &camera;
    defaultRender1.viewport = &viewport_tl;
    defaultRender1.framebuffer = nullptr;
    defaultRender1.visitor = &visitor;

    Rendered defaultRender2;
    defaultRender2.scene = vaoScene2;
    defaultRender2.camera = &camera;
    defaultRender2.viewport = &viewport_tr;
    defaultRender2.framebuffer = nullptr;
    defaultRender2.visitor = &visitor;

    Rendered defaultRender3;
    defaultRender3.scene = vaoScene3;
    defaultRender3.camera = &camera;
    defaultRender3.viewport = &viewport_br;
    defaultRender3.framebuffer = nullptr;
    defaultRender3.visitor = &visitor;

    GLFWApplicationEvents interface(&camera);

    app->setInterface(&interface);

    app->addRendered(&fboRender);
    app->addRendered(&defaultRender1);
    app->addRendered(&defaultRender2);
    app->addRendered(&defaultRender3);

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

	return 0;
}
