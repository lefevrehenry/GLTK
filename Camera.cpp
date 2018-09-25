#include "Camera.h"

// Glm
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace gl;

Camera::Camera() :
    m_projectionType(Perspective),
    m_orthoLeft(0),
    m_orthoRight(0),
    m_orthoBottom(0),
    m_orthoTop(0),
    m_fovy(0),
    m_aspectRatio(0),
    m_zNear(0),
    m_zFar(0),
    m_model(),
    m_view(),
    m_proj(),
    m_mvp(),
    m_normal(),
    m_target(),
    m_mvpDirty(true),
    m_normalDirty(true)
{

}

Camera::~Camera()
{

}

glm::vec3 Camera::right() const
{
    glm::vec4 right = glm::column(this->m_model, 0);
    return glm::vec3(right);
}

glm::vec3 Camera::up() const
{
    glm::vec4 up = glm::column(this->m_model, 1);
    return glm::vec3(up);
}

glm::vec3 Camera::direction() const
{
    glm::vec4 direction = glm::column(this->m_model, 2);
    return glm::vec3(direction);
}

glm::vec3 Camera::eye() const
{
    glm::vec4 eye = glm::column(this->m_model, 3);
    return glm::vec3(eye);
}

const glm::mat4& Camera::model() const
{
    return this->m_model;
}

const glm::mat4& Camera::view() const
{
    return this->m_view;
}

const glm::mat4& Camera::projection() const
{
    return this->m_proj;
}

const glm::mat4& Camera::mvp() const
{
    if (isMvpDirty()) {
        this->m_mvp = projection() * view();
        setMvpDirty(false);
    }
    return this->m_mvp;
}

const glm::mat3& Camera::normal() const
{
    if (isNormalDirty()) {
        this->m_normal = glm::inverseTranspose(glm::mat3(view()));
        setNormalDirty(false);
    }
    return this->m_normal;
}

void Camera::rotate(float theta, float phi)
{
    // we want to rotate camera moving on a sphere centered on
    // m_target by the angle theta (around oz) and angle phi (around oy)

    glm::mat4 transform;

    transform = glm::translate(glm::mat4(), this->m_target);
    transform = glm::rotate(transform, -theta, up());
    transform = glm::rotate(transform, phi, right());
    transform = glm::translate(transform, -this->m_target);

    this->m_model = transform * this->m_model;
    this->m_view = glm::inverse( this->m_model );

    setMvpDirty(true);
    setNormalDirty(true);
}

void Camera::lookAt(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up)
{
    this->m_target = glm::vec3(target);
    this->m_view = glm::lookAt(eye, target, up);
    this->m_model = glm::inverse( this->m_view );

    setMvpDirty(true);
    setNormalDirty(true);
}

void Camera::perspective(float fovy, float aspect, float zNear, float zFar)
{
    this->m_projectionType = Perspective;
    this->m_fovy = fovy;
    this->m_aspectRatio = aspect;
    this->m_zNear = zNear;
    this->m_zFar = zFar;

    this->m_proj = glm::perspective(fovy, aspect, zNear, zFar);

    setMvpDirty(true);
}

void Camera::orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
    this->m_projectionType = Orthograhic;
    this->m_orthoLeft = left;
    this->m_orthoRight = right;
    this->m_orthoBottom = bottom;
    this->m_orthoTop = top;
    this->m_zNear = zNear;
    this->m_zFar = zFar;

    this->m_proj = glm::ortho(left, right, bottom, top, zNear, zFar);

    setMvpDirty(true);
}

glm::mat4 Camera::projectionROI(float bounds[4]) const
{
    glm::mat4 projection;

    if (this->m_projectionType == Orthograhic) {
        float l = m_orthoLeft   + (m_orthoRight - m_orthoLeft) * bounds[0];
        float r = m_orthoLeft   + (m_orthoRight - m_orthoLeft) * bounds[1];
        float b = m_orthoBottom + (m_orthoTop - m_orthoBottom) * bounds[2];
        float t = m_orthoBottom + (m_orthoTop - m_orthoBottom) * bounds[3];
        float n = m_zNear;
        float f = m_zFar;
        projection = glm::ortho(l, r, b, t, n, f);
    } else {
        float ymax = m_zNear * glm::atan(this->m_fovy / 2.0f);
        float xmax = ymax * this->m_aspectRatio;
        float l = -xmax + (2.0f * xmax) * bounds[0];
        float r = -xmax + (2.0f * xmax) * bounds[1];
        float b = -ymax + (2.0f * ymax) * bounds[2];
        float t = -ymax + (2.0f * ymax) * bounds[3];
        float n = m_zNear;
        float f = m_zFar;
        projection = glm::frustum(l, r, b, t, n, f);
    }

    return projection;
}

bool Camera::isMvpDirty() const
{
    return this->m_mvpDirty;
}

bool Camera::isNormalDirty() const
{
    return this->m_normalDirty;
}

void Camera::setMvpDirty(bool dirty) const
{
    this->m_mvpDirty = dirty;
}

void Camera::setNormalDirty(bool dirty) const
{
    this->m_normalDirty = dirty;
}
