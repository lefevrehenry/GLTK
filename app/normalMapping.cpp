
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
    basicTexturingShader->set(OpenGLState::CullFace, GL_FALSE);

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

    Light light;
    light.setPosition(glm::vec3(0,0,0));
    light.setDirection(glm::vec3(0,0,-1));
    light.setColor(glm::vec3(1,1,1));

    VisualManager::UpdateUniformBufferLight(light);

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
