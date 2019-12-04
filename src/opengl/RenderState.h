#ifndef GLTK_RENDERSTATE_H
#define GLTK_RENDERSTATE_H

#include <OpenGLAttribute.h>

// Standard Library
#include <map>


namespace gl {

/**
 * @brief The RenderSate class
 */
class RenderSate
{

public:
    RenderSate();

public:
    template< AttributeName N >
    void setState(typename OpenGL<N>::Type value)
    {
        this->m_attributeStack[N] = OpenGLAttribut<N>::Create(value);
    }

public:
    void pushAttribute() const;
    void popAttribute() const;

private:
    std::map< AttributeName, BaseOpenGLAttribut::SPtr > m_attributeStack;

};

}   // namespace gl

#endif
