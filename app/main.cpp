
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <Mesh.h>
#include <Message.h>
#include <Scene.h>

#include <Helper.h>
#include <Program.h>
#include <ShaderProgram.h>
#include <VisualModel.h>
#include <VisualOption.h>

// OpenGL
#include <GL/gl.h>


using namespace gl;

int main()
{
    /* Create a window and its OpenGL context */
    GLFWApplication* app = GLFWApplication::CreateWindow();

    if (!app)
        return -1;

//    helper::DataRepository.addFirstPath("/home/henry/");
//    helper::DataRepository.addFirstPath("/home/henry/dev");
//    helper::DataRepository.addLastPath("/test");
//    helper::DataRepository.print();

    int glMajor;
    int glMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);

    msg_info("OpenGL") << "Congrat's ! You're running OpenGL " << glMajor << "." << glMinor;

//    GLint bound[4];

//    glViewport(3,5,20,30);
//    glGetIntegerv(GL_VIEWPORT, &bound[0]);
//    msg_info("Viewport") << bound[0] << ", " << bound[1] << " | " << bound[2] << ", " << bound[3];

//    glPushAttrib(GL_VIEWPORT_BIT);

//    glViewport(9,3,10,10);
//    glGetIntegerv(GL_VIEWPORT, &bound[0]);
//    msg_info("Viewport") << bound[0] << ", " << bound[1] << " | " << bound[2] << ", " << bound[3];

//    glPopAttrib();

//    glGetIntegerv(GL_VIEWPORT, &bound[0]);
//    msg_info("Viewport") << bound[0] << ", " << bound[1] << " | " << bound[2] << ", " << bound[3];

    /* Create your scene here */
    Node* root = app->getScene()->root();
    Node* node1 = root->addChild();
    Node* node2 = root->addChild();

    ShaderProgram* shaderProgram[2];

//    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::FlatShading);
    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::PhongShading);
//    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::Texturing);
//    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::HighLight);

    root->setShaderProgram(shaderProgram[0]);


    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/Armadillo_simplified.obj");
    Mesh* mesh2 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/dragon_low.obj");
//    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/cube.obj");
//    Mesh* mesh2 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/sphere.obj");

    // Node 1
    VisualModel visual1(mesh1, Material::Bronze());
//    visual1.transform().translate(-40,0,0);
//    visual1.transform().scale(10,10,10);
    node1->addVisual(&visual1);

    // Node 2
    VisualModel visual2(mesh2, Material::Obsidian());
    node2->addVisual(&visual2);

    app->getScene()->fitCamera();

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

//    delete mesh1;
//    delete mesh2;
//    delete shaderProgram[0];
//    delete shaderProgram[1];

	return 0;
}
