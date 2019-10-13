#ifndef OPENGLATTRIBUT_H
#define OPENGLATTRIBUT_H

#include <gltk.h>
#include <misc/Light.h>
#include <opengl/VisualManager.h>

// OpenGL
#include <GL/gl.h>

// Standard Library
#include <array>
#include <memory>


namespace gl {

enum AttributeName
{
    ClearColor,
    CullFace,
    DepthFunc,
    DepthMask,
    DepthTest,
    LineWidth,
    PolygonMode,
    Viewport,
    SceneLight
};

GLTK::OpenGLDepthFunc OpenGLToGLTKDepthFunc(GLenum);
GLenum GLTKToOpenglDepthFunc(GLTK::OpenGLDepthFunc);

/**
 * @brief The OpenGL class
 */
template< AttributeName N >
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
struct OpenGL<LineWidth>
{
    using Type = GLfloat;

    static Type Get()
    {
        Type value;

        glGetFloatv(GL_LINE_WIDTH, &value);

        return value;
    }
    static void Set(Type value)
    {
        glLineWidth(value);
    }
};

template<>
struct OpenGL<PolygonMode>
{
    using Type = GLenum;

    static Type Get()
    {
        int value;

        glGetIntegerv(GL_POLYGON_MODE, &value);

        return Type(value);
    }
    static void Set(Type value)
    {
        glPolygonMode(GL_FRONT_AND_BACK, value);
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

template<>
struct OpenGL<SceneLight>
{
    using Type = Light;

    static Type Get()
    {
        Type value = VisualManager::GetLight();

        return value;
    }
    static void Set(Type value)
    {
        VisualManager::UpdateUniformBufferLight(value);
    }
};

class OpenGLStateMachine;

/**
 * @brief The BaseOpenGLAttribut class
 */
class BaseOpenGLAttribut
{
public:
    using Type = void;
    using SPtr = std::shared_ptr< BaseOpenGLAttribut >;
};

/**
 * @brief The OpenGLAttribut class
 */
template< AttributeName N >
class OpenGLAttribut : public BaseOpenGLAttribut
{

public:
    using Type = typename OpenGL<N>::Type;
    using SPtr = std::shared_ptr< OpenGLAttribut<N> >;

public:
    OpenGLAttribut(const Type& value) :
        m_value(value)
    {
    }

public:
    Type value() const
    {
       return this->m_value;
    }
    void setValue(const Type& value)
    {
        this->m_value = value;
    }

public:
    static SPtr Create(const Type& value)
    {
        return SPtr(new OpenGLAttribut<N>(value));
    }

private:
    Type m_value;

};

}   // namespace gl

#endif
