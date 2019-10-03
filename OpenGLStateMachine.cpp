#include "OpenGLStateMachine.inl"

using namespace gl;
using namespace gl::statemachine;

std::map< AttributeName, std::stack<BaseOpenGLAttribut::SPtr> > OpenGLStateMachine::MapOpenGLStateMachineAttribute;
