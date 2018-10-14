#ifndef FRAMEOBJECT_H
#define FRAMEOBJECT_H

#include "Camera.h"

// Standard Library
#include<vector>


namespace gl {

class Framebuffer;

/**
 * @brief The FrameObject class
 */
class FrameObject
{

public:
    FrameObject();
    virtual ~FrameObject();

public:
    void addChild(FrameObject* frameObject);
    void removeChild(unsigned int i);

    unsigned int getNbChild() const;
    const FrameObject* getChild(unsigned int i) const;

private:
    std::vector<FrameObject*> m_frameObjects;

};


/**
 * @brief The FrameCamera class
 */
class FrameCamera : public FrameObject
{

public:
    FrameCamera();

public:
    Camera& camera();

private:
    Camera m_camera;

};

/**
 * @brief The Viewport class
 */
class Viewport : public FrameObject
{

public:
    Viewport(float x, float y, float rw, float rh);

private:
    float m_x;
    float m_y;
    float m_rw;
    float m_rh;

};

/**
 * @brief The DefaultFramebufferObject class
 */
class DefaultFramebufferObject : public FrameObject
{

public:
    DefaultFramebufferObject();

};

/**
 * @brief The FramebufferObject class
 */
class FramebufferObject : public FrameObject
{

public:
    FramebufferObject(Framebuffer* framebuffer);

private:
    const Framebuffer* m_framebuffer;

};

}

#endif
