#include "Selectable.h"

using namespace gl;

Selectable::Selectable() :
    m_visualModel(nullptr),
    m_position()
{

}

Selectable::~Selectable()
{

}

const VisualModel* Selectable::visualModel() const
{
    return this->m_visualModel;
}

void Selectable::setVisualModel(const VisualModel* visualModel)
{
    this->m_visualModel = visualModel;
}

glm::vec4 Selectable::position() const
{
    return this->m_position;
}

void Selectable::setPosition(const glm::vec4& position)
{
    this->m_position = glm::vec4(position);
}
