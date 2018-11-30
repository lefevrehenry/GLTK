
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
    cubeMapShader->set(OpenGLState::DepthFunc, GL_LEQUAL);
    cubeMapShader->set(OpenGLState::CullFace, GL_FALSE);

    VisualModel* vaoQuad = new VisualModel("mesh/cube.obj");
    childNode->addVisual(vaoQuad);
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

    //////////////// Scene

    SceneGraph* scene = createScene();
    Camera camera;

    scene->fitView(&camera);

    //////////////// Render pass

    Rendered defaultRender1;
    defaultRender1.scene = scene;
    defaultRender1.camera = &camera;

    app->addRendered(&defaultRender1);

    //////////////// Interface

    GLFWApplicationEvents interface(&camera);
    app->setInterface(&interface);

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

	return 0;
}
