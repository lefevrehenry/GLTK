#include "RenderState.h"

#include <OpenGLStateMachine.h>

using namespace gl;

RenderSate::RenderSate() :
    m_attributeStack()
{

}

template< AttributeName N >
void PushAndApply(BaseOpenGLAttribut::SPtr baseAttribut)
{
    typename OpenGLAttribut<N>::SPtr attribut = std::static_pointer_cast< OpenGLAttribut<N> >(baseAttribut);

    OpenGLStateMachine::Push<N>();
    OpenGLStateMachine::Set<N>(*attribut);
}

void RenderSate::pushAttribute() const
{
    // ugly as fuck !
    // mixing compile-time template compilation with runtime check :/
    // implement a static_for loop ?
    // but probably a bad idea to use template in this case

    for (auto it : this->m_attributeStack) {
        AttributeName attribute = it.first;
        BaseOpenGLAttribut::SPtr value = it.second;

        switch (attribute) {
        case ClearColor:
            PushAndApply<ClearColor>(value);
            break;
        case CullFace:
            PushAndApply<CullFace>(value);
            break;
        case DepthFunc:
            PushAndApply<DepthFunc>(value);
            break;
        case DepthMask:
            PushAndApply<DepthMask>(value);
            break;
        case DepthTest:
            PushAndApply<DepthTest>(value);
            break;
        case LineWidth:
            PushAndApply<LineWidth>(value);
            break;
        case PolygonMode:
            PushAndApply<PolygonMode>(value);
            break;
        case SceneLight:
            PushAndApply<SceneLight>(value);
            break;
        case Viewport:
            PushAndApply<Viewport>(value);
            break;
        }
    }
}

void RenderSate::popAttribute() const
{
    // same as above, ugly idea

    for (auto it : this->m_attributeStack) {
        AttributeName attribute = it.first;

        switch (attribute) {
        case ClearColor:
            OpenGLStateMachine::Pop<ClearColor>();
            break;
        case CullFace:
            OpenGLStateMachine::Pop<CullFace>();
            break;
        case DepthFunc:
            OpenGLStateMachine::Pop<DepthFunc>();
            break;
        case DepthMask:
            OpenGLStateMachine::Pop<DepthMask>();
            break;
        case DepthTest:
            OpenGLStateMachine::Pop<DepthTest>();
            break;
        case LineWidth:
            OpenGLStateMachine::Pop<LineWidth>();
            break;
        case PolygonMode:
            OpenGLStateMachine::Pop<PolygonMode>();
            break;
        case SceneLight:
            OpenGLStateMachine::Pop<SceneLight>();
            break;
        case Viewport:
            OpenGLStateMachine::Pop<Viewport>();
            break;
        }
    }
}
