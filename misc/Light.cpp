#include "Light.h"

// Glm
#include <glm/gtc/matrix_access.hpp>

using namespace gl;

Light::Light() :
    m_position(),
    m_direction(),
    m_color(),
    m_matrix(),
    m_isDirty(true)
{

}

Light::Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color) :
    m_position(position),
    m_direction(direction),
    m_color(color),
    m_matrix(),
    m_isDirty(true)
{

}

Light::~Light()
{

}

const glm::mat3& Light::matrix() const
{
    if (this->m_isDirty) {
        m_matrix = glm::column(m_matrix, 0, this->m_position);
        m_matrix = glm::column(m_matrix, 1, this->m_direction);
        m_matrix = glm::column(m_matrix, 2, this->m_color);
        this->m_isDirty = false;
    }

    return m_matrix;
}

const glm::vec3& Light::position() const
{
    return this->m_position;
}

void Light::setPosition(const glm::vec3& position)
{
    this->m_position = position;
    this->m_isDirty = true;
}

const glm::vec3& Light::direction() const
{
    return this->m_direction;
}

void Light::setDirection(const glm::vec3& direction)
{
    this->m_direction = direction;
    this->m_isDirty = true;
}

const glm::vec3& Light::color() const
{
    return this->m_color;
}

void Light::setColor(const glm::vec3& color)
{
    this->m_color = color;
    this->m_isDirty = true;
}
