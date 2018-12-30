#ifndef OPENGLSTATEMACHINE_H
#define OPENGLSTATEMACHINE_H

#include "Message.h"
#include "OpenGLAttribute.h"

// Gl
#include <GL/gl.h>

// Standard Library
#include <map>
#include <stack>


namespace gl {

class OpenGLStateMachine;

/**
 * @brief The BaseOpenGLStateMachineAttribute class
 */
class BaseOpenGLStateMachineAttribute
{
    friend class OpenGLStateMachine;

public:
    virtual ~BaseOpenGLStateMachineAttribute();

private:
    virtual void pushAttribute() = 0;
    virtual void popAttribute() = 0;

};

/**
 * @brief The OpenGLStateMachineAttribute class
 */
template <StateAttribute S>
class OpenGLStateMachineAttribute : public BaseOpenGLStateMachineAttribute
{

private:
    virtual void pushAttribute()
    {
        msg_warning("OpenGLStateMachine") << "pushAttribute not specialized yet";
    }
    virtual void popAttribute()
    {
        msg_warning("OpenGLStateMachine") << "popAttribute not specialized yet";
    }

private:
    std::stack< BaseOpenGLAttribute* >  m_stack;

};

/**
 * @brief The OpenGLStateMachine class
 */
class OpenGLStateMachine
{

public:
    OpenGLStateMachine() = delete;

public:
    static void Push(StateAttribute attribute);
    static void Pop(StateAttribute attribute);

public:
    static void Apply(StateAttribute attribute, BaseOpenGLAttribute* value);

private:
    static std::map< StateAttribute, BaseOpenGLStateMachineAttribute* > MapOpenGLStateMachineAttribute;

};

}   // namespace gl

#endif
