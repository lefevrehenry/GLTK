#ifndef VISUALMANAGER_H
#define VISUALMANAGER_H

#include "Camera.h"
#include "Light.h"
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
        CameraIndex = 3,
        LightIndex = 4
    };

public:
    static void Init();
    static void Clean();

public:
    static void UpdateUniformBufferTransform(const gl::Transform& transform);
    static void UpdateUniformBufferMaterial(const gl::Material& material);
    static void UpdateUniformBufferCamera(const gl::Camera& camera);
    static void UpdateUniformBufferLight(const Light& light);

private:
    static GLuint m_uboTransform;
    static GLuint m_uboMaterial;
    static GLuint m_uboCamera;
    static GLuint m_uboLight;

};

}   // namespace gl

#endif
