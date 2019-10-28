#include "VisualOption.h"

using namespace gl;

VisualOption::VisualOption() :
    m_polygonMode(FILL)
{

}

VisualOption::~VisualOption()
{

}

void VisualOption::push() const
{
//    glPushAttrib(GL_POLYGON_BIT);
//    glPolygonMode(GL_FRONT_AND_BACK, this->m_polygonMode);
}

void VisualOption::pop() const
{
//    glPopAttrib();
}

VisualOption::FillMode VisualOption::fillMode() const
{
    return this->m_polygonMode;
}

void VisualOption::setFillMode(FillMode polygonMode)
{
    this->m_polygonMode = polygonMode;
}
