#ifndef CAMERA_H
#define CAMERA_H

// Glm
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


namespace gl
{

/**
 * @brief The Camera class
 */
class Camera
{

public:

    enum ProjectionType {
        Perspective,
        Orthograhic
    };

    Camera(ProjectionType projectionType);
    virtual ~Camera();

public:

    bool isDirty() const;

    const glm::mat3 normal();

    const glm::mat4& model();

    const glm::mat4& view();

    const glm::mat4& projection();

    void rotate(float rx, float ry);

    void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

    void perspective(float fovy, float aspect, float zNear, float zFar);

    void orthographic(float left, float right, float bottom, float top, float zNear, float zFar);

private:

    void setModelDirty(bool dirty);
    void setViewDirty(bool dirty);
    void setProjectionDirty(bool dirty);

private:
    ProjectionType m_projectionType;

    glm::quat m_orientation;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_proj;

    glm::vec3 m_eye;
    glm::vec3 m_target;
    glm::vec3 m_up;

    bool m_modelDirty;
    bool m_viewDirty;
    bool m_projectionDirty;

};

}   // namespace gl

#endif
