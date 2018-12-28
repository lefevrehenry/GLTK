#include "OpenGLStateMachine.h"

namespace gl {

template<>
void OpenGLStateMachineAttribute<float, 4>::pushAttribute()
{
    std::array<float, 4> values;
    glGetFloatv(GL_COLOR_CLEAR_VALUE, values.data());

    this->m_stack.push(values);
}

template<>
void OpenGLStateMachineAttribute<float, 4>::popAttribute()
{
    std::array<float, 4>& values = this->m_stack.top();
    glClearColor(values[0], values[1], values[2], values[3]);

    this->m_stack.pop();
}

}   // namespace gl
