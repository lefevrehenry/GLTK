#ifndef OPENGLSTATEMACHINE_H
#define OPENGLSTATEMACHINE_H

#include <Message.h>
#include <OpenGLAttribute.h>

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
        typename OpenGLAttribut<N>::SPtr attribut( new OpenGLAttribut<N>(OpenGLStateMachine::Get<N>()) );

        OpenGLStateMachineStackAttribute[N].push(attribut);
    }
    template< AttributeName N >
    static void Pop()
    {
        // cast the top item of the stack and set it
        BaseOpenGLAttribut::SPtr baseAttribut = OpenGLStateMachineStackAttribute[N].top();
        typename OpenGLAttribut<N>::SPtr attribut = std::static_pointer_cast< OpenGLAttribut<N> >(baseAttribut);

        OpenGLStateMachineStackAttribute[N].pop();

        OpenGLStateMachine::Set<N>(*attribut);
    }

public:
    template< AttributeName N >
    static OpenGLAttribut<N> Get()
    {
        // get an OpenGLAttribut with the current OpenGL state
        typename OpenGL<N>::Type value = OpenGL<N>::Get();

        return OpenGLAttribut<N>(value);
    }
    template< AttributeName N >
    static void Set(const OpenGLAttribut<N>& attribut)
    {
        // set the OpenGL state with the OpenGLAttribut
        OpenGL<N>::Set(attribut.value());
    }

public:
    static std::map< AttributeName, std::stack<BaseOpenGLAttribut::SPtr> > OpenGLStateMachineStackAttribute;

};

}   // namespace gl

#endif
