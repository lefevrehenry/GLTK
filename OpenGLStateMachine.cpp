#include "OpenGLStateMachine.inl"

using namespace gl;


class Factory
{
public:
    template<StateAttribute S>
    static BaseOpenGLStateMachineAttribute* Create()
    {
        msg_warning("Factory") << "Factory::Create<>() function not specialized for StateAttribute " << S;
        return nullptr;
    }
};

template<>
BaseOpenGLStateMachineAttribute* Factory::Create<ClearColor>() {
    return new OpenGLStateMachineAttribute<float,4>();
}


std::map< StateAttribute, BaseOpenGLStateMachineAttribute* > OpenGLStateMachine::MapOpenGLStateMachineAttribute = {
    std::make_pair(ClearColor, Factory::Create<ClearColor>())
};

BaseOpenGLStateMachineAttribute::~BaseOpenGLStateMachineAttribute()
{

}

void OpenGLStateMachine::Push(StateAttribute attribute)
{
    BaseOpenGLStateMachineAttribute* base = MapOpenGLStateMachineAttribute[attribute];
    base->pushAttribute();
}

void OpenGLStateMachine::Pop(StateAttribute attribute)
{
    BaseOpenGLStateMachineAttribute* base = MapOpenGLStateMachineAttribute[attribute];
    base->popAttribute();
}
