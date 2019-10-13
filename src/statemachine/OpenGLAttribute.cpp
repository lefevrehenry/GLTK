#include "OpenGLAttribute.inl"

using namespace gl;

GLTK::OpenGLDepthFunc OpenGLToGLTKDepthFunc(const GLenum& param)
{
    switch(param)
    {
    case GL_NEVER:
        return GLTK::OpenGLDepthFunc::Never;
    case GL_LESS:
        return GLTK::OpenGLDepthFunc::Less;
    case GL_EQUAL:
        return GLTK::OpenGLDepthFunc::Equal;
    case GL_LEQUAL:
        return GLTK::OpenGLDepthFunc::Lequal;
    case GL_GREATER:
        return GLTK::OpenGLDepthFunc::Greater;
    case GL_NOTEQUAL:
        return GLTK::OpenGLDepthFunc::NotEqual;
    case GL_GEQUAL:
        return GLTK::OpenGLDepthFunc::Gequal;
    case GL_ALWAYS:
        return GLTK::OpenGLDepthFunc::Always;
    default:
        return GLTK::OpenGLDepthFunc::Less;
    }
}

GLenum GLTKToOpenglDepthFunc(const GLTK::OpenGLDepthFunc& param)
{
    switch(param)
    {
    case GLTK::OpenGLDepthFunc::Never:
        return GL_NEVER;
    case GLTK::OpenGLDepthFunc::Less:
        return GL_LESS;
    case GLTK::OpenGLDepthFunc::Equal:
        return GL_EQUAL;
    case GLTK::OpenGLDepthFunc::Lequal:
        return GL_LEQUAL;
    case GLTK::OpenGLDepthFunc::Greater:
        return GL_GREATER;
    case GLTK::OpenGLDepthFunc::NotEqual:
        return GL_NOTEQUAL;
    case GLTK::OpenGLDepthFunc::Gequal:
        return GL_GEQUAL;
    case GLTK::OpenGLDepthFunc::Always:
        return GL_ALWAYS;
    }

    return GL_NONE;
}
