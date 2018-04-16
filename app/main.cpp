
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

    /* Create your scene here */
    Node* root = app->getScene()->root();
    Node* node1 = root->addChild();
    Node* node2 = root->addChild();

//    typedef VisualOption::PolygonMode PolygonMode;
//    VisualOption visualOption;
//    visualOption.setPolygonMode(PolygonMode::LINE);

    ShaderProgram* shaderProgram[2];

//    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::FlatShading);
    shaderProgram[1] = helper::CreateShaderProgram(ShaderProgram::PhongShading);
//    shaderProgram = helper::CreateShaderProgram(ShaderProgram::Texturing);
    shaderProgram[0] = helper::CreateShaderProgram(ShaderProgram::HighLight);

//    root->setShaderProgram(shaderProgram);
    node1->setShaderProgram(shaderProgram[0]);
    node2->setShaderProgram(shaderProgram[1]);


//    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/Armadillo_simplified.obj");
//    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/dragon_low.obj");
    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/cube.obj");
    Mesh* mesh2 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/sphere.obj");

    // Node 1
    VisualModel visual1(mesh1);
    visual1.material() = Material::Bronze();
    visual1.transform().translate(-40,0,0);
    visual1.transform().scale(10,10,10);
    node1->addVisual(&visual1);

    // Node 2
    VisualModel visual2(mesh2);
//    visual2.transform().translate(2,0,0);
    visual2.material() = Material::Obsidian();
    node2->addVisual(&visual2);

    app->getScene()->fitCamera();

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

    delete mesh1;
    delete mesh2;
    delete shaderProgram[0];
    delete shaderProgram[1];

	return 0;
}
