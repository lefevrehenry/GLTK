#ifndef GLTK_TRANSFORM_H
#define GLTK_TRANSFORM_H

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace gl {

/**
 * @brief The Transform class
 */
class Transform
{

public:
    Transform();

public:
    const glm::mat4& matrix() const;

public:
    static Transform inverse(const Transform& transform);

//public:
//    void setTranslation(float x, float y, float z);
//    void setTranslation(const glm::vec3& translate);

public:
    void translate(float x, float y, float z);
    void translate(const glm::vec3& translate);

    void rotate(const glm::quat& quat);
    void rotate(float radian, const glm::vec3& axis);

    void scale(float sx, float sy, float sz);
    void scale(const glm::vec3& scale);

public:
    Transform operator*(float t) const;
    Transform& operator*=(float t);

    Transform operator*(const Transform& other) const;
    Transform& operator*=(const Transform& other);

    Transform operator-(const Transform& other) const;
    Transform& operator-=(const Transform& other);

public:
    glm::vec3 m_translation;
    glm::quat m_orientation;
    glm::vec3 m_scale;

    mutable glm::mat4 m_transform;

    mutable bool m_isDirty;

};

}   // namespace gl

#endif
