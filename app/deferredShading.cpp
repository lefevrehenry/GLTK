
#include <FileRepository.h>
#include <Framebuffer.h>
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

SceneGraph* createScene()
{
    SceneGraph* scene = new SceneGraph();

    Node* root = scene->root();
    Node* childNode;

    ////////////////////////////////////////

    childNode = root->addChild();

    VisualModel* vm = new VisualModel("mesh/dragon_low.obj", Material::Gold());
    childNode->addVisual(vm);

    return scene;
}

SceneGraph* createVaoScene(Texture* textureColor)
{
    SceneGraph* scene = new SceneGraph();
    Node* root = scene->root();

    VisualModel* vaoQuad = new VisualModel("mesh/vaoQuad.obj");
    root->addVisual(vaoQuad);

    ShaderProgram* shaderProgram = helper::CreateShaderProgram(ShaderProgram::VaoQuad);
    shaderProgram->addData<Texture>("textureColor", *textureColor);
    root->setShaderProgram(shaderProgram);

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


static GLFWApplication* app = nullptr;
static GLFWApplicationEvents* interface = nullptr;
static Framebuffer* fbo = nullptr;
static Rendered fboRender;
static Rendered defaultRender2;
static Rendered defaultRender3;
static Rendered defaultRender4;

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

    if (!app)
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

    unsigned int width = GLFWApplication::ScreenWidth;
    unsigned int height = GLFWApplication::ScreenHeight;

    ShaderProgram* deferredShader = helper::CreateShaderProgram(ShaderProgram::Deferred);
    ShaderVisitor* deferredShaderVisitor = new ShaderVisitor(deferredShader);

    //////////////// Scene

    SceneGraph* scene = createScene();
    Camera* camera = new Camera();

    fitView(scene, camera);

    //// --------------------------------
    /// Dessine les textures de couleur, normale et pofondeur dans un fbo
    fbo = new Framebuffer(width, height);
    fbo->attachTexture();
    fbo->attachTexture();
    fbo->attachTexture();
    fbo->attachDepthTexture();

    fboRender.scene = scene;
    fboRender.camera = camera;
    fboRender.visitor = deferredShaderVisitor;

    //////////////// Render pass

    SceneGraph* vaoScene2 = createVaoScene(fbo->renderTexture(0));
    SceneGraph* vaoScene3 = createVaoScene(fbo->renderTexture(1));
    SceneGraph* vaoScene4 = createVaoScene(fbo->renderTexture(2));

    defaultRender2.scene = vaoScene2;
    defaultRender2.camera = camera;

    defaultRender3.scene = vaoScene3;
    defaultRender3.camera = camera;

    defaultRender4.scene = vaoScene4;
    defaultRender4.camera = camera;

    //////////////// Interface

    interface = new GLFWApplicationEvents(camera);
    app->setInterface(interface);

    app->setDrawCallBack(displayCallback);
}

void displayCallback()
{
    fbo->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width = int(fbo->width());
    int height = int(fbo->height());
    glViewport(0, 0, width, height);

    fboRender.draw();

    fbo->unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    width = int(GLFWApplication::ScreenWidth) / 2;
    height = int(GLFWApplication::ScreenHeight) / 2;
    glViewport(0, 0, width, height);

    defaultRender2.draw();

    glViewport(width, 0, width, height);
    defaultRender3.draw();

    glViewport(0, height, width, height);
    defaultRender4.draw();
}

void errorCallback(int, const char* description)
{
    // Throw an error
    throw (description);
}
