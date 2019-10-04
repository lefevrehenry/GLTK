#include "OpenGLStateMachine.inl"

using namespace gl;

std::map< AttributeName, std::stack<BaseOpenGLAttribut::SPtr> > OpenGLStateMachine::MapOpenGLStateMachineAttribute;
