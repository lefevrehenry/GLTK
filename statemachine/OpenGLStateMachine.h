#ifndef OPENGLSTATEMACHINE_H
#define OPENGLSTATEMACHINE_H

#include <helper/Message.h>
#include <statemachine/OpenGLAttribute.h>

// Standard Library
#include <map>
#include <stack>


namespace gl {

/**
 * @brief The OpenGLStateMachine class
 */
class OpenGLStateMachine
{

public:
    OpenGLStateMachine() = delete;

public:
    template< AttributeName N >
    static void Push()
    {
        // create an OpenGLAttribut with the current OpenGL state and store it
        typename OpenGLAttribut<N>::SPtr attribut = OpenGLStateMachine::Get<N>();

        MapOpenGLStateMachineAttribute[N].push(attribut);
    }
    template< AttributeName N >
    static void Pop()
    {
        // cast the top item of the stack and set it
        BaseOpenGLAttribut::SPtr baseAttribut = MapOpenGLStateMachineAttribute[N].top();
        typename OpenGLAttribut<N>::SPtr attribut = std::static_pointer_cast< OpenGLAttribut<N> >(baseAttribut);

        MapOpenGLStateMachineAttribute[N].pop();

        OpenGLStateMachine::Set<N>(attribut);
    }

public:
    template< AttributeName N >
    static typename OpenGLAttribut<N>::SPtr Get()
    {
        // get an OpenGLAttribut with the current OpenGL state
        typename OpenGL<N>::Type value = OpenGL<N>::Get();

        return OpenGLAttribut<N>::Create(value);
    }
    template< AttributeName N >
    static void Set(typename OpenGLAttribut<N>::SPtr attribut)
    {
        // set the OpenGL state with the OpenGLAttribut
        OpenGL<N>::Set(attribut->value());
    }

public:
    static std::map< AttributeName, std::stack<BaseOpenGLAttribut::SPtr> > MapOpenGLStateMachineAttribute;

};

}   // namespace gl

#endif
