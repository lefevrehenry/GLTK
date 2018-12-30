#include "OpenGLStateMachine.inl"

using namespace gl;

// completly useless factory
class Factory
{
public:
    template <StateAttribute S>
    static BaseOpenGLStateMachineAttribute* Create()
    {
        return new OpenGLStateMachineAttribute<S>();
    }
};

std::map< StateAttribute, BaseOpenGLStateMachineAttribute* > OpenGLStateMachine::MapOpenGLStateMachineAttribute = {
    std::make_pair(ClearColor, Factory::Create<ClearColor>()),
    std::make_pair(CullFace, Factory::Create<CullFace>()),
    std::make_pair(DepthFunc, Factory::Create<DepthFunc>()),
    std::make_pair(DepthMask, Factory::Create<DepthMask>()),
    std::make_pair(DepthTest, Factory::Create<DepthTest>())
};

BaseOpenGLStateMachineAttribute::~BaseOpenGLStateMachineAttribute()
{

}

void OpenGLStateMachine::Push(StateAttribute attribute)
{
    BaseOpenGLStateMachineAttribute* base = MapOpenGLStateMachineAttribute[attribute];

    if (base != nullptr)
        base->pushAttribute();
    else
        msg_warning("OpenGLStateMachine") << "Cannot push unknown attribute. No keys match the desired attribute " << attribute;
}

void OpenGLStateMachine::Pop(StateAttribute attribute)
{
    BaseOpenGLStateMachineAttribute* base = MapOpenGLStateMachineAttribute[attribute];

    if (base != nullptr)
        base->popAttribute();
    else
        msg_warning("OpenGLStateMachine") << "Cannot pop unknown attribute";
}

void OpenGLStateMachine::Apply(StateAttribute attribute, BaseOpenGLAttribute* base)
{
    if (attribute == ClearColor) {
        OpenGLAttribute<float,4>* value = static_cast< OpenGLAttribute<float,4>* >(base);

        if (value == nullptr)
            return;

        glClearColor(value->x(),value->y(),value->z(),value->w());

    } else if (attribute == CullFace) {
        OpenGLAttribute<GLboolean,1>* value = static_cast< OpenGLAttribute<GLboolean,1>* >(base);

        if (value == nullptr)
            return;

        if(value->x() == GL_TRUE)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);

    } else if (attribute == DepthFunc) {
        OpenGLAttribute<int,1>* value = static_cast< OpenGLAttribute<int,1>* >(base);

        if (value == nullptr)
            return;

        GLenum depthFunc = GLenum(value->x());
        glDepthFunc(depthFunc);

    } else if (attribute == DepthMask) {
        OpenGLAttribute<GLboolean,1>* value = static_cast< OpenGLAttribute<GLboolean,1>* >(base);

        if (value == nullptr)
            return;

        glDepthMask(value->x());

    } else if (attribute == DepthTest) {
        OpenGLAttribute<GLboolean,1>* value = static_cast< OpenGLAttribute<GLboolean,1>* >(base);

        if (value == nullptr)
            return;

        if (value->x() == GL_TRUE)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }
}
