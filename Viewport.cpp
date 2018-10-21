#include "Viewport.h"

using namespace gl;

Viewport::Viewport() :
    m_x(0),
    m_y(0),
    m_rw(0),
    m_rh(0)
{

}

Viewport::Viewport(float x, float y, float rw, float rh) :
    m_x(x),
    m_y(y),
    m_rw(rw),
    m_rh(rh)
{

}

float Viewport::x() const
{
    return m_x;
}

float Viewport::y() const
{
    return m_y;
}

float Viewport::rw() const
{
    return m_rw;
}

float Viewport::rh() const
{
    return m_rh;
}

void Viewport::set(float x, float y, float rw, float rh)
{
    this->m_x = x;
    this->m_y = y;
    this->m_rw = rw;
    this->m_rh = rh;
}
