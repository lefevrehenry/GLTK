
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

    if (i == 1 && j == 0) {
        visualModel->transform().rotate(glm::pi<float>()/2.f, glm::vec3(0,1,0));
        visualModel->transform().scale(1,5,5);
    }
    node->addVisual(visualModel);
}

void addMatCapShader(Node* node, std::string filename) {
    Texture* matcapTexture = new Texture2D();
    matcapTexture->load(filename);

    ShaderProgram* shaderProgram = helper::CreateShaderProgram(ShaderProgram::MatCap);
    shaderProgram->addData<Texture>("matcap", *matcapTexture);

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

    Texture* boardAmbientTex = new Texture2D();
    boardAmbientTex->load("textures/Brick_Wall_ambient.jpg");

    Texture* boardColorTex = new Texture2D();
    boardColorTex->load("textures/Brick_Wall_color.jpg");

    Texture* boardNormalTex = new Texture2D();
    boardNormalTex->load("textures/Brick_Wall_normal.jpg");

    Texture* boardSpecTex = new Texture2D();
    boardSpecTex->load("textures/Brick_Wall_spec.jpg");

    ShaderProgram* shaderProgram = helper::CreateShaderProgram(ShaderProgram::NormalMapping);
    shaderProgram->addData<glm::vec3>("dir_light", glm::vec3(0,0,-1));
    shaderProgram->addData<Texture>("ambientMap", *boardAmbientTex);
    shaderProgram->addData<Texture>("colorMap", *boardColorTex);
    shaderProgram->addData<Texture>("normalMap", *boardNormalTex);
    shaderProgram->addData<Texture>("specMap", *boardSpecTex);

    VisualModel* board = new VisualModel("models/flatQuad.obj");
    float s = 118.5;
    board->transform().scale(s,s,s);
//    board->transform().rotate(glm::pi<float>()/2.f, glm::vec3(0,1,0));

    node->setShaderProgram( shaderProgram );
    node->addVisual(board);

    // White Set

    Node* nodeWhite = node->addChild();
    addMatCapShader(nodeWhite, "textures/m8.jpg");

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

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    createChessboard(root);

    return scene;
}

Camera bestFitFromDirection(SceneGraph* scene, const glm::vec3& direction)
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
    glm::vec3 eye = target - (glm::normalize(direction) * (diagonal / 2.0f));
    glm::vec3 up(0,0,1);
    camera.lookAt(eye, target, up);

    // projection
//    float fovy = 45.0f;
//    float aspect = 4.0f / 3.0f;
//    float zNear = 0.05f * diagonal;
//    float zFar = diagonal;
//    camera.perspective(fovy, aspect, zNear, zFar);

    float half_diag = diagonal / 2.0f;
    float left = -half_diag;
    float right = half_diag;
    float bottom = -half_diag;
    float top = half_diag;
    camera.orthographic(left, right, bottom, top, 0, diagonal);

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
    Camera camera;// = bestFitFromDirection(scene, glm::vec3(-1,-1,-1));
    Viewport viewport(0,0,1,1);
    DrawVisitor drawVisitor;

    scene->fitView(&camera);

    Camera light = bestFitFromDirection(scene, glm::vec3(-1,-1,-1));

    ShaderProgram* deferredShader = helper::CreateShaderProgram(ShaderProgram::Deferred);
    ShaderVisitor deferredShaderVisitor(deferredShader);

//    ShaderProgram* shadowMappingShader = helper::CreateShaderProgram(ShaderProgram::ShadowMapping);
//    ShaderVisitor shadowMappingVisitor(shadowMappingShader);

    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;

//    //// --------------------------------
//    /// Dessine la texture de couleur de la scene
//    Framebuffer fboColor(width, height);
//    fboColor.attachTexture();
//    fboColor.attachDepthTexture();

//    Rendered fboColorRender;
//    fboColorRender.scene = scene;
//    fboColorRender.camera = &camera;
//    fboColorRender.viewport = &viewport;
//    fboColorRender.framebuffer = &fboColor;
//    fboColorRender.visitor = &drawVisitor;

    //// --------------------------------
    /// Dessine les textures de couleur, normale et pofondeur
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
    fboRender.visitor = &deferredShaderVisitor;

//    //// --------------------------------
//    /// Dessine la scene du point de vue de la lumiere
//    Framebuffer fboLight(width, height);
//    fboLight.attachTexture();
//    fboLight.attachTexture();
//    fboLight.attachTexture();
//    fboLight.attachDepthTexture();

//    Rendered fboRenderLight;
//    fboRenderLight.scene = scene;
//    fboRenderLight.camera = &light;
//    fboRenderLight.viewport = &viewport;
//    fboRenderLight.framebuffer = &fboLight;
//    fboRenderLight.visitor = &deferredShaderVisitor;
//    fboRenderLight.singleShot = true;

//    //// --------------------------------
//    /// Dessine les ombres de la scene
//    Framebuffer fboShadow(width, height);
//    fboShadow.attachTexture();
//    fboShadow.attachDepthTexture();

//    Rendered fboRenderShadow;
//    fboRenderShadow.scene = scene;
//    fboRenderShadow.camera = &camera;
//    fboRenderShadow.viewport = &viewport;
//    fboRenderShadow.framebuffer = &fboShadow;
//    fboRenderShadow.visitor = &shadowMappingVisitor;

//    glm::mat4 biasMatrix(
//        0.5, 0.0, 0.0, 0.0,
//        0.0, 0.5, 0.0, 0.0,
//        0.0, 0.0, 0.5, 0.0,
//        0.5, 0.5, 0.5, 1.0
//    );

//    shadowMappingShader->addData<glm::mat4>("LightCam", biasMatrix * light.mvp());
//    shadowMappingShader->addData<Texture>("depthLight", *fboLight.depthTexture());
//    shadowMappingShader->addData<Texture>("colorTexture", *fboColor.renderTexture(0));


//    SceneGraph* vaoScene1 = createVaoScene(fboColor.renderTexture(0));
    SceneGraph* vaoScene2 = createVaoScene(fbo.renderTexture(0));
    SceneGraph* vaoScene3 = createVaoScene(fbo.renderTexture(1));
    SceneGraph* vaoScene4 = createVaoScene(fbo.renderTexture(2));
//    SceneGraph* vaoScene5 = createVaoScene(fboLight.renderTexture(2));
//    SceneGraph* vaoScene6 = createVaoScene(fboShadow.renderTexture(0));

    Viewport viewport_bl( 0, 0,.5,.5);
    Viewport viewport_br(.5, 0,.5,.5);
    Viewport viewport_tl( 0,.5,.5,.5);
    Viewport viewport_tr(.5,.5,.5,.5);

//    Rendered defaultRender1;
//    defaultRender1.scene = scene;
//    defaultRender1.camera = &camera;
//    defaultRender1.viewport = &viewport_tl;
//    defaultRender1.framebuffer = nullptr;
//    defaultRender1.visitor = &visitor;

//    Rendered defaultRender1;
//    defaultRender1.scene = vaoScene1;
//    defaultRender1.camera = &camera;
//    defaultRender1.viewport = &viewport_tl;
//    defaultRender1.framebuffer = nullptr;
//    defaultRender1.visitor = &drawVisitor;

    Rendered defaultRender2;
    defaultRender2.scene = vaoScene2;
    defaultRender2.camera = &camera;
    defaultRender2.viewport = &viewport_tr;
    defaultRender2.framebuffer = nullptr;
    defaultRender2.visitor = &drawVisitor;

    Rendered defaultRender3;
    defaultRender3.scene = vaoScene3;
    defaultRender3.camera = &camera;
    defaultRender3.viewport = &viewport_br;
    defaultRender3.framebuffer = nullptr;
    defaultRender3.visitor = &drawVisitor;

    Rendered defaultRender4;
    defaultRender4.scene = vaoScene4;
    defaultRender4.camera = &camera;
    defaultRender4.viewport = &viewport_bl;
    defaultRender4.framebuffer = nullptr;
    defaultRender4.visitor = &drawVisitor;

//    Rendered defaultRender5;
//    defaultRender5.scene = vaoScene5;
//    defaultRender5.camera = &camera;
//    defaultRender5.viewport = &viewport_bl;
//    defaultRender5.framebuffer = nullptr;
//    defaultRender5.visitor = &drawVisitor;

//    Rendered defaultRender6;
//    defaultRender6.scene = vaoScene6;
//    defaultRender6.camera = &camera;
//    defaultRender6.viewport = &viewport_br;
//    defaultRender6.framebuffer = nullptr;
//    defaultRender6.visitor = &drawVisitor;

//    app->addRendered(&fboColorRender);
//    app->addRendered(&defaultRender1);

    app->addRendered(&fboRender);
    app->addRendered(&defaultRender2);
    app->addRendered(&defaultRender3);
    app->addRendered(&defaultRender4);

//    app->addRendered(&fboRenderLight);
//    app->addRendered(&defaultRender5);

//    app->addRendered(&fboRenderShadow);
//    app->addRendered(&defaultRender6);

    GLFWApplicationEvents interface(&camera);
    app->setInterface(&interface);

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

	return 0;
}
