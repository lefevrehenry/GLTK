#ifndef GLTK_H
#define GLTK_H

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <array>

namespace gl {

enum AttributName
{
    ClearColor,
    CullFace,
    DepthFunc,
    DepthMask,
    DepthTest,
    Viewport,
    Count
};

/**
 * @brief The OpenGL class
 */
template <AttributName N>
struct OpenGL
{
    using Type = void;
};

template<>
struct OpenGL<ClearColor>
{
    using Type = std::array<GLfloat,4>;

    static Type Get()
    {
        Type value;

        glGetFloatv(GL_COLOR_CLEAR_VALUE, value.data());

        return value;
    }
    static void Set(Type value)
    {
        glClearColor(value[0],value[1],value[2],value[3]);
    }
};

template<>
struct OpenGL<CullFace>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_CULL_FACE, &value);

        return value;
    }
    static void Set(Type value)
    {
        if(value == GL_TRUE)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
    }
};

template<>
struct OpenGL<DepthFunc>
{
    using Type = GLenum;

    static Type Get()
    {
        int value;

        glGetIntegerv(GL_DEPTH_FUNC, &value);

        return Type(value);
    }
    static void Set(Type value)
    {
        glDepthFunc(value);
    }
};

template<>
struct OpenGL<DepthMask>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_DEPTH_WRITEMASK, &value);

        return value;
    }
    static void Set(Type value)
    {
        glDepthMask(value);
    }
};

template<>
struct OpenGL<DepthTest>
{
    using Type = GLboolean;

    static Type Get()
    {
        Type value;

        glGetBooleanv(GL_DEPTH_TEST, &value);

        return value;
    }
    static void Set(Type value)
    {
        if(value == GL_TRUE)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }
};

template<>
struct OpenGL<Viewport>
{
    using Type = std::array<GLint,4>;

    static Type Get()
    {
        Type value;

        glGetIntegerv(GL_VIEWPORT, value.data());

        return value;
    }
    static void Set(Type value)
    {
        glViewport(value[0],value[1],value[2],value[3]);
    }
};

extern template struct OpenGL<ClearColor>;
extern template struct OpenGL<CullFace>;
extern template struct OpenGL<DepthFunc>;
extern template struct OpenGL<DepthMask>;
extern template struct OpenGL<DepthTest>;
extern template struct OpenGL<Viewport>;

}

#endif
