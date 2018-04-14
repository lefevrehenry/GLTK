
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

//void print()
//{
//    GLint polyMode;
//    glGetIntegerv(GL_POLYGON_MODE, &polyMode);

//    if ( polyMode == GL_POINT )
//        msg_info("Visu") << "POINT";
//    if ( polyMode == GL_LINE )
//        msg_info("Visu") << "LINE";
//    if ( polyMode == GL_FILL )
//        msg_info("Visu") << "FILL";
//}

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

    typedef VisualOption::PolygonMode PolygonMode;

    VisualOption visualOption;
    visualOption.setPolygonMode(PolygonMode::LINE);

    ShaderProgram* shaderProgram = nullptr;

    shaderProgram = helper::CreateShaderProgram(ShaderProgram::PhongShading);
    node1->setShaderProgram(shaderProgram);

    shaderProgram = helper::CreateShaderProgram(ShaderProgram::FlatShading);
//    shaderProgram = helper::CreateShaderProgram(ShaderProgram::Texturing);
    node2->setShaderProgram(shaderProgram);

    Mesh* mesh1 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/Armadillo_simplified.obj");
    Mesh* mesh2 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/dragon_low.obj");
//    Mesh* mesh2 = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/cube.obj");

    // Node 1
    VisualModel visual1(mesh1);
    visual1.transform().translate(10,0,0);
    visual1.material() = Material::Bronze();
    node1->addVisual(&visual1);
    node1->setVisualOption(&visualOption);

    // Node 2
    VisualModel visual2(mesh2);
    visual2.material() = Material::Obsidian();
    node2->addVisual(&visual2);

    app->getScene()->fitCamera();

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

    /*delete mesh1;*/ delete mesh2;
    /*mesh1 = nullptr;*/ mesh2 = nullptr;

    delete shaderProgram;
    shaderProgram = nullptr;

	return 0;
}
