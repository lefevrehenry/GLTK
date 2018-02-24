
#include "GLFWApplication.h"
#include "Message.h"

// Glew
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Glut
#include <GL/glut.h>

static gl::GLFWApplication* app = nullptr;

#ifndef USE_GLUT

void draw() {
    if (window) {
        /* Call to drawing function */
        window->draw();

        /* Swap front and back buffers */
        glutSwapBuffers();

        /* Marks the current window as needing to be redisplayed */
        glutPostRedisplay();
    }
}

void reshape(int width, int height) {
    if (window)
        window->reshape(width, height);
}

void keyboardInput(unsigned char key, int x, int y) {
    if (window)
        window->keyboardInput(key, x, y);
}

int main(int argc, char* argv[])
{
    // Glut initialization
    glutInit(&argc, argv);

    // image with 4 channels + double buffering + depth buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("OpenGL");

    // Glew initialization
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        // Problem: glewInit failed, something is seriously wrong.
        return EXIT_FAILURE;
    }

    int major = 0;
    int minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    msg_info("OpenGL") << "Congrat's ! You're running OpenGL " << major << "." << minor;

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardInput);

    window = gl::MainWindow::getInstance();

    glutMainLoop();

    return 0;
}

#else

int main(int argc, char* argv[])
{
    /* GLFW initialization */
    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* windowHandle = glfwCreateWindow(640, 480, "OpenGL", nullptr, nullptr);

    if (!windowHandle)
    {
        glfwTerminate();
        msg_error("GLFW") << "Cannot create a window and its opengl context";
        return EXIT_FAILURE;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(windowHandle);

    // Glew initialization
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        // Problem: glewInit failed, something is seriously wrong.
        msg_error("OpenGL") << "Glew init failed";
        return EXIT_FAILURE;
    }

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    msg_info("OpenGL") << "Congrat's ! You're running OpenGL " << major << "." << minor;

    app = gl::GLFWApplication::getInstance();
    app->init();
    app->setWindow(windowHandle);

    app->loop();

    app->setWindow(nullptr);
    glfwDestroyWindow(windowHandle);

    glfwTerminate();

	return 0;
}

#endif
