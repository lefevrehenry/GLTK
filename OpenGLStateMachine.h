#ifndef OpenGLSTATEMACHINE_H
#define OpenGLSTATEMACHINE_H

#include "Message.h"

// Gl
#include <GL/gl.h>

// Standard Library
#include <array>
#include <map>
#include <stack>


namespace gl {

enum StateAttribute {
//    DepthMask,
//    DepthTest,
//    DepthFunc,
//    CullFace,
    ClearColor
};

/**
 * @brief The BaseOpenGLStateMachineAttribute class
 */
class BaseOpenGLStateMachineAttribute
{
public:
    virtual ~BaseOpenGLStateMachineAttribute();

public:
    virtual void pushAttribute() = 0;
    virtual void popAttribute() = 0;

};

/**
 * @brief The OpenGLStateMachineAttribute class
 */
template <typename T, int N>
class OpenGLStateMachineAttribute : public BaseOpenGLStateMachineAttribute
{

    static_assert (N > 0, "Non positive size array not allowed");

public:
    virtual void pushAttribute()
    {
        msg_warning("OpenGLStateMachine") << "attribute not implemented yet";
    }
    virtual void popAttribute()
    {
        msg_warning("OpenGLStateMachine") << "attribute not implemented yet";
    }

protected:
    std::stack< std::array<T,N> >   m_stack;

};

/**
 * @brief The OpenGLStateMachine class
 */
class OpenGLStateMachine
{

private:
    OpenGLStateMachine();
    virtual ~OpenGLStateMachine();

public:
    static void Push(StateAttribute attribute);
    static void Pop(StateAttribute attribute);

private:
    static std::map< StateAttribute, BaseOpenGLStateMachineAttribute* > MapOpenGLStateMachineAttribute;

};

}   // namespace gl

#endif
