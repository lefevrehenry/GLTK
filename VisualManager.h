#ifndef VISUALMANAGER_H
#define VISUALMANAGER_H

#include "Camera.h"
#include "Material.h"
#include "Transform.h"

// Glew
#include <GL/glew.h>


namespace gl {

/**
 * @brief The VisualManager class
 */
class VisualManager
{

public:
    enum {
        TransformIndex = 1,
        MaterialIndex = 2,
        CameraIndex = 3
    };

public:
    static void Init();
    static void Clean();

public:
    static void UpdateUniformBufferTransform(const gl::Transform& transform);
    static void UpdateUniformBufferMaterial(const gl::Material& material);
    static void UpdateUniformBufferCamera(const gl::Camera& camera);

private:
    static GLuint m_uboTransform;
    static GLuint m_uboMaterial;
    static GLuint m_uboCamera;

};

}   // namespace gl

#endif
