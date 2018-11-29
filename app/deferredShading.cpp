
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
#include <ShaderProgram.h>
#include <VisualModel.h>
#include <Texture.h>
#include <Visitor.h>

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <map>
#include <string>

using namespace gl;
using namespace gl::helper;

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    Node* childNode;

    ////////////////////////////////////////

    childNode = root->addChild();

    VisualModel* vm = new VisualModel("models/dragon_low.obj", Material::Gold());
    childNode->addVisual(vm);

    return scene;
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

    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;

    ShaderProgram* deferredShader = helper::CreateShaderProgram(ShaderProgram::Deferred);
    ShaderVisitor deferredShaderVisitor(deferredShader);

    //////////////// Scene

    SceneGraph* scene = createScene();
    Camera camera;

    scene->fitView(&camera);

    //// --------------------------------
    /// Dessine les textures de couleur, normale et pofondeur dans un fbo
    Framebuffer fbo(width, height);
    fbo.attachTexture();
    fbo.attachTexture();
    fbo.attachTexture();
    fbo.attachDepthTexture();

    Rendered fboRender;
    fboRender.scene = scene;
    fboRender.camera = &camera;
    fboRender.framebuffer = &fbo;
    fboRender.visitor = &deferredShaderVisitor;

    //////////////// Render pass

    SceneGraph* vaoScene2 = createVaoScene(fbo.renderTexture(0));
    SceneGraph* vaoScene3 = createVaoScene(fbo.renderTexture(1));
    SceneGraph* vaoScene4 = createVaoScene(fbo.renderTexture(2));

    Viewport viewport_bl( 0, 0,.5,.5);
    Viewport viewport_br(.5, 0,.5,.5);
    Viewport viewport_tl( 0,.5,.5,.5);
    Viewport viewport_tr(.5,.5,.5,.5);

    Rendered defaultRender2;
    defaultRender2.scene = vaoScene2;
    defaultRender2.camera = &camera;
    defaultRender2.viewport = &viewport_tr;
    defaultRender2.framebuffer = nullptr;

    Rendered defaultRender3;
    defaultRender3.scene = vaoScene3;
    defaultRender3.camera = &camera;
    defaultRender3.viewport = &viewport_br;
    defaultRender3.framebuffer = nullptr;

    Rendered defaultRender4;
    defaultRender4.scene = vaoScene4;
    defaultRender4.camera = &camera;
    defaultRender4.viewport = &viewport_bl;
    defaultRender4.framebuffer = nullptr;

    app->addRendered(&fboRender);
    app->addRendered(&defaultRender2);
    app->addRendered(&defaultRender3);
    app->addRendered(&defaultRender4);

    //////////////// Interface

    GLFWApplicationEvents interface(&camera);
    app->setInterface(&interface);

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

    return 0;
}
