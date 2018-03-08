#ifndef TRANSFORM_H
#define TRANSFORM_H

// Standard Library
//#include <string>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// OpenGL
//#include <GL/glew.h>


namespace gl {

/**
 * @brief The Transform class
 */
class Transform
{

public:
    Transform();
    virtual ~Transform();

public:

    const glm::mat4& getMatrix() const;

public:
    void translate(float x, float y, float z);
    void translate(const glm::vec3& translate);

    void rotate(const glm::quat& quat);
    void rotate(float radian, const glm::vec3& axis);

    void scale(float sx, float sy, float sz);
    void scale(const glm::vec3& scale);

private:

    mutable glm::mat4 m_transform;

    glm::vec3 m_translation;
    glm::quat m_orientation;
    glm::vec3 m_scale;

    mutable bool m_isDirty;

};

}   // namespace gl

#endif
