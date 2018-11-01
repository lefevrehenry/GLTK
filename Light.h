#ifndef LIGHT_H
#define LIGHT_H

// Glm
#include <glm/glm.hpp>


namespace gl {

/**
 * @brief The Light class
 */
class Light
{

public:
    Light();
    Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);
    virtual ~Light();

public:
    const glm::mat3& matrix() const;

public:
    const glm::vec3& position() const;
    void setPosition(const glm::vec3& position);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    const glm::vec3& color() const;
    void setColor(const glm::vec3& color);

private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_color;

    mutable glm::mat3 m_matrix;
    mutable bool m_isDirty;

};

}   // namespace gl

#endif
