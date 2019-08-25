#ifndef OPENGLATTRIBUT_H
#define OPENGLATTRIBUT_H

#include "GLTK.h"

// Standard Library
#include <memory>


namespace gl {

class OpenGLStateMachine;

/**
 * @brief The BaseOpenGLAttribut class
 */
class BaseOpenGLAttribut
{
public:
    using SPtr = std::shared_ptr< BaseOpenGLAttribut >;
};

/**
 * @brief The OpenGLAttribut class
 */
template< AttributName N >
class OpenGLAttribut : public BaseOpenGLAttribut
{
    friend class OpenGLStateMachine;

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

private:
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

}  // namespace gl

#endif
