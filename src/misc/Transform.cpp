#include "Transform.h"

// Glm
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>


using namespace gl;

Transform::Transform() :
    m_translation(0,0,0),
    m_orientation(1,0,0,0),
    m_scale(1,1,1),
    m_transform(),
    m_isDirty(true)
{

}

const glm::mat4& Transform::matrix() const
{
    if (this->m_isDirty) {
        glm::mat4 tr = glm::translate(this->m_translation);
        glm::mat4 rt = glm::toMat4(this->m_orientation);
        glm::mat4 sc = glm::scale(this->m_scale);

        this->m_transform = tr * rt * sc;
        this->unmarkDirty();
    }

    return this->m_transform;
}

Transform Transform::inverse(const Transform& transform)
{
    Transform result;

    result.m_translation = -transform.m_translation;
    result.m_orientation = glm::inverse(transform.m_orientation);
    result.m_scale /= transform.m_scale;

    return result;
}

void Transform::setTranslation(float x, float y, float z)
{
    this->m_translation.x = x;
    this->m_translation.y = y;
    this->m_translation.z = z;
    this->markDirty();
}

void Transform::setTranslation(const glm::vec3& translation)
{
    this->setTranslation(translation.x, translation.y, translation.z);
}

void Transform::setQuaternion(const glm::quat& quaternion)
{
    this->m_orientation = glm::normalize(quaternion);
    this->markDirty();
}

void Transform::setQuaternion(float radian, const glm::vec3& axis)
{
    glm::quat quat = glm::angleAxis(radian, glm::normalize(axis));
    setQuaternion(quat);
}

void Transform::setScale(float sx, float sy, float sz)
{
    this->m_scale.x = sx;
    this->m_scale.y = sy;
    this->m_scale.z = sz;
    this->markDirty();
}

void Transform::setScale(const glm::vec3& scale)
{
    this->setScale(scale.x, scale.y, scale.z);
}

void Transform::translate(float x, float y, float z)
{
    this->m_translation.x += x;
    this->m_translation.y += y;
    this->m_translation.z += z;
    this->markDirty();
}

void Transform::translate(const glm::vec3& translation)
{
    this->translate(translation.x, translation.y, translation.z);
}

void Transform::rotate(const glm::quat& quaternion)
{
    this->m_orientation = glm::normalize(quaternion * this->m_orientation);
    this->markDirty();
}

void Transform::rotate(float radian, const glm::vec3& axis)
{
    glm::quat quat = glm::angleAxis(radian, axis);
    this->rotate(quat);
}

void Transform::scale(float sx, float sy, float sz)
{
    this->m_scale.x *= sx;
    this->m_scale.y *= sy;
    this->m_scale.z *= sz;
    this->markDirty();
}

void Transform::scale(const glm::vec3& scale)
{
    this->scale(scale.x, scale.y, scale.z);
}

Transform Transform::operator*(const Transform& other) const
{
    Transform result(*this);
    result *= other;

    return result;
}

Transform& Transform::operator*=(const Transform& other)
{
    this->m_translation += other.m_translation;
    this->m_orientation *= other.m_orientation;
    this->m_scale *= other.m_scale;

    return *this;
}

Transform Transform::operator-(const Transform& other) const
{
    Transform result(*this);
    result -= other;

    return result;
}

Transform& Transform::operator-=(const Transform& other)
{
    this->m_translation -= other.m_translation;
    this->m_orientation *= glm::inverse(other.m_orientation);
    this->m_scale /= other.m_scale;

    return *this;
}

void Transform::markDirty() const
{
    this->m_isDirty = true;
}

void Transform::unmarkDirty() const
{
    this->m_isDirty = false;
}

Transform& Transform::operator*=(float t)
{
    this->m_translation *= t;

    glm::quat q = m_orientation;
    glm::vec3 axis = glm::axis(q);
    glm::quat unit = glm::angleAxis(0.f, axis);
    this->m_orientation = glm::mix(unit, q, t);

    this->m_scale *= t;

    return *this;
}

Transform Transform::operator*(float t) const
{
    Transform result(*this);
    result *= t;

    return result;
}
