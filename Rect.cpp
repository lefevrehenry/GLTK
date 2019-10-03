#include "Rect.h"

using namespace gl;
using namespace gl::misc;

Rect::Rect() :
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(0)
{

}

Rect::Rect(int x, int y, int width, int height) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{

}

int Rect::x() const
{
    return m_x;
}

int Rect::y() const
{
    return m_y;
}

int Rect::width() const
{
    return m_width;
}

int Rect::height() const
{
    return m_height;
}

bool Rect::contains(int x, int y) const
{
    return (x >= this->m_x && x <= this->m_x + this->m_width - 1 && y >= this->m_y && y <= this->m_y + this->m_height - 1);
}

void Rect::set(int x, int y, int width, int height)
{
    this->m_x = x;
    this->m_y = y;
    this->m_width = width;
    this->m_height = height;
}
