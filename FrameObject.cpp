#include "FrameObject.h"

using namespace gl;

FrameObject::FrameObject()
{

}

FrameObject::~FrameObject()
{

}

void FrameObject::addChild(FrameObject* frameObject)
{
    this->m_frameObjects.push_back(frameObject);
}

void FrameObject::removeChild(unsigned int i)
{
    if (i >= getNbChild())
        return;

    this->m_frameObjects.erase(this->m_frameObjects.begin() + i);
}

unsigned int FrameObject::getNbChild() const
{
    return this->m_frameObjects.size();
}

const FrameObject* FrameObject::getChild(unsigned int i) const
{
    if (i >= getNbChild())
        return nullptr;

    return this->m_frameObjects[i];
}

FrameCamera::FrameCamera() : FrameObject(),
    m_camera()
{

}

Viewport::Viewport(float x, float y, float rw, float rh) : FrameObject (),
    m_x(x),
    m_y(y),
    m_rw(rw),
    m_rh(rh)
{

}

DefaultFramebufferObject::DefaultFramebufferObject() : FrameObject ()
{

}

FramebufferObject::FramebufferObject(Framebuffer* framebuffer) : FrameObject (),
    m_framebuffer(framebuffer)
{

}
