#include "Camera.h"

// Glm
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace gl;

Camera::Camera(ProjectionType projectionType) :
    m_projectionType(projectionType),
    m_orientation(),
    m_model(),
    m_view(),
    m_proj(),
    m_eye(),
    m_target(),
    m_up(),
    m_modelDirty(true),
    m_viewDirty(true),
    m_projectionDirty(true)
{

}

Camera::~Camera()
{

}

bool Camera::isDirty() const
{
    return (/*m_modelDirty ||*/ m_viewDirty || m_projectionDirty);
}

const glm::mat3 Camera::normal()
{
    return glm::inverseTranspose(glm::mat3(model()));
}

const glm::mat4 &Camera::model()
{
    return this->m_model;
}

const glm::mat4& Camera::view()
{
    if (this->m_viewDirty) {
        this->m_view = glm::inverse(model());
        setViewDirty(false);
    }
    return this->m_view;
}

const glm::mat4& Camera::projection()
{
    if (this->m_projectionDirty) {
        setProjectionDirty(false);
    }
    return this->m_proj;
}

void Camera::rotate(float rx, float ry)
{
    // we want to rotate camera moving on a sphere centered on
    // m_target by the angle rx (around oz) and angle ry (around oy)

    // we apply the opposite rotation for the world
    float dTheta = -rx;
    float dPhi = -ry;

    // fetch the two rotations axis (world coord)
    glm::vec4 right = glm::column(this->m_model, 0);
    glm::vec4 up    = glm::column(this->m_model, 1);

    // compute corresponding quaternion
    glm::quat q1 = glm::angleAxis(dTheta, glm::vec3(up));
    glm::quat q2 = glm::angleAxis(-dPhi, glm::vec3(right));
    glm::quat q = q2 * q1;

    glm::mat4& model = this->m_model;

    // orient the world, m_target as center of rotation
    model = glm::translate(model, this->m_target);
    model = glm::toMat4(q) * model;
    model = glm::translate(model, -this->m_target);

//    // get vector corresponding to the angle (dTheta,dPhi)
//    float costheta = glm::cos(dTheta);
//    float sintheta = glm::sin(dTheta);
//    float cosphi = glm::cos(dPhi);
//    float sinphi = glm::sin(dPhi);

//    // the parametrized vector starts from -z axis
//    float z = -costheta * cosphi;
//    float x = -sintheta * cosphi;
//    float y = sinphi;

//    // compute corresponding quaternion (sphere coord system)
//    glm::vec3 src(0,0,-1);
//    glm::vec3 dest(x, y, z);

//    // position the two vectors on the world
//    glm::quat qw(this->m_model);
//    src = glm::rotate(qw, src);
//    dest = glm::rotate(qw, dest);

//    // compute corresponding quaternion (world coord)
//    glm::quat q = glm::rotation(src, dest);

//    glm::mat4& model = this->m_model;

//    // orient the world, m_target as center of rotation
//    model = glm::translate(model, this->m_target);
//    this->m_model = glm::toMat4(q) * this->m_model;
//    model = glm::translate(model, -this->m_target);

    setViewDirty(true);
}

void Camera::lookAt(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up)
{
    this->m_eye = glm::vec3(eye);
    this->m_target = glm::vec3(target);
    this->m_up = glm::vec3(up);
    this->m_view = glm::lookAt(eye, target, up);

    this->m_model = glm::inverse( this->m_view );

    setViewDirty(false);
}

void Camera::perspective(float fovy, float aspect, float zNear, float zFar)
{
    this->m_projectionType = Perspective;
    this->m_proj = glm::perspective(fovy, aspect, zNear, zFar);
    setProjectionDirty(false);
}

void Camera::orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
    this->m_projectionType = Orthograhic;
    this->m_proj = glm::ortho(left, right, bottom, top, zNear, zFar);
    setProjectionDirty(false);
}

void Camera::setModelDirty(bool dirty)
{
    this->m_modelDirty = dirty;
}

void Camera::setViewDirty(bool dirty)
{
    this->m_viewDirty = dirty;
}

void Camera::setProjectionDirty(bool dirty)
{
    this->m_projectionDirty = dirty;
}
