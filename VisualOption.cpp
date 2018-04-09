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

VisualOption::PolygonMode VisualOption::getPolygonMode() const
{
    return this->m_polygonMode;
}

void VisualOption::setPolygonMode(PolygonMode polygonMode)
{
    this->m_polygonMode = polygonMode;
}
