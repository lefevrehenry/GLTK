
#include <FileRepository.h>
#include <GLFWApplication.h>
#include <Mesh.h>
#include <Message.h>
#include <Scene.h>

#include <Program.h>
#include <ShaderProgram.h>

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
    Mesh* mesh = Mesh::FromFile("/home/henry/dev/QtProject/OpenGL/share/models/teapot.obj");
    app->getScene()->addMesh(mesh);

    Program* program = app->addProgram();
    program->addShaderProgram(ShaderProgram::PhongShading);

    app->getScene()->fit();

    /* Throws the main loop */
    app->loop();

    GLFWApplication::Terminate();

	return 0;
}
