#include "OpenGLStateMachine.h"

namespace gl {

//////////////////////////// ClearColor

template<>
void OpenGLStateMachineAttribute<ClearColor>::pushAttribute()
{
    OpenGLAttribute<float,4>* value = new OpenGLAttribute<float,4>();
    glGetFloatv(GL_COLOR_CLEAR_VALUE, value->data());

    this->m_stack.push(value);
}

template<>
void OpenGLStateMachineAttribute<ClearColor>::popAttribute()
{
    BaseOpenGLAttribute* base = this->m_stack.top();
    OpenGLStateMachine::Apply(ClearColor, base);

    this->m_stack.pop();

    delete base;
}

//////////////////////////// CullFace

template<>
void OpenGLStateMachineAttribute<CullFace>::pushAttribute()
{
    OpenGLAttribute<GLboolean,1>* value = new OpenGLAttribute<GLboolean,1>();
    glGetBooleanv(GL_CULL_FACE, value->data());

    this->m_stack.push(value);
}

template<>
void OpenGLStateMachineAttribute<CullFace>::popAttribute()
{
    BaseOpenGLAttribute* base = this->m_stack.top();
    OpenGLStateMachine::Apply(CullFace, base);

    this->m_stack.pop();

    delete base;
}

//////////////////////////// DepthFunc

template<>
void OpenGLStateMachineAttribute<DepthFunc>::pushAttribute()
{
    OpenGLAttribute<int,1>* value = new OpenGLAttribute<int,1>();
    glGetIntegerv(GL_DEPTH_FUNC, value->data());

    this->m_stack.push(value);
}

template<>
void OpenGLStateMachineAttribute<DepthFunc>::popAttribute()
{
    BaseOpenGLAttribute* base = this->m_stack.top();
    OpenGLStateMachine::Apply(DepthFunc, base);

    this->m_stack.pop();

    delete base;
}

//////////////////////////// DepthMask

template<>
void OpenGLStateMachineAttribute<DepthMask>::pushAttribute()
{
    OpenGLAttribute<GLboolean,1>* value = new OpenGLAttribute<GLboolean,1>();
    glGetBooleanv(GL_DEPTH_WRITEMASK, value->data());

    this->m_stack.push(value);
}

template<>
void OpenGLStateMachineAttribute<DepthMask>::popAttribute()
{
    BaseOpenGLAttribute* base = this->m_stack.top();
    OpenGLStateMachine::Apply(DepthMask, base);

    this->m_stack.pop();

    delete base;
}

//////////////////////////// DepthTest

template<>
void OpenGLStateMachineAttribute<DepthTest>::pushAttribute()
{
    OpenGLAttribute<GLboolean,1>* value = new OpenGLAttribute<GLboolean,1>();
    glGetBooleanv(GL_DEPTH_TEST, value->data());

    this->m_stack.push(value);
}

template<>
void OpenGLStateMachineAttribute<DepthTest>::popAttribute()
{
    BaseOpenGLAttribute* base = this->m_stack.top();
    OpenGLStateMachine::Apply(DepthTest, base);

    this->m_stack.pop();

    delete base;
}

}   // namespace gl
