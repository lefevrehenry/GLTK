#include "Viewport.h"

using namespace gl;

Viewport::Viewport() :
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(0)
{

}

Viewport::Viewport(int x, int y, int width, int height) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{

}

int Viewport::x() const
{
    return m_x;
}

int Viewport::y() const
{
    return m_y;
}

int Viewport::width() const
{
    return m_width;
}

int Viewport::height() const
{
    return m_height;
}

bool Viewport::contains(int x, int y) const
{
    return (x >= this->m_x && x <= this->m_x + this->m_width - 1 && y >= this->m_y && y <= this->m_y + this->m_height - 1);
}

void Viewport::set(int x, int y, int width, int height)
{
    this->m_x = x;
    this->m_y = y;
    this->m_width = width;
    this->m_height = height;
}
