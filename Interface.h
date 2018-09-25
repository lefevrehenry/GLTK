#ifndef INTERFACE_H
#define INTERFACE_H


class GLFWwindow;

namespace gl {

/**
 * @brief The Interface class
 */
class Interface
{

public:

    virtual ~Interface();

    virtual void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) = 0;

    virtual void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos) = 0;

    virtual void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset) = 0;

    virtual void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) = 0;

};

/**
 * @brief The DefaultInterface class
 */
class DefaultInterface : public Interface
{

public:

    virtual void mouseButtonCallback(GLFWwindow*, int, int, int) {}

    virtual void cursorPosCallback(GLFWwindow*, double, double) {}

    virtual void scrollCallback(GLFWwindow*, double, double) {}

    virtual void keyCallback(GLFWwindow*, int, int, int, int) {}

};

}   // namespace gl

#endif
