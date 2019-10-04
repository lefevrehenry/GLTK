#ifndef VISUALMANAGER_H
#define VISUALMANAGER_H

#include <misc/Camera.h>
#include <misc/Light.h>
#include <misc/Material.h>
#include <misc/Transform.h>

// Glew
#include <GL/glew.h>


namespace gl {

/**
 * @brief The VisualManager class
 */
class VisualManager
{

public:
    VisualManager() = delete;

public:
    enum {
        TransformIndex = 1,
        MaterialIndex = 2,
        CameraIndex = 3,
        LightIndex = 4,
        TimeIndex = 5
    };

public:
    static void Init();
    static void Clean();

public:
    static void UpdateUniformBufferTransform(const gl::Transform& transform);
    static void UpdateUniformBufferMaterial(const gl::Material& material);
    static void UpdateUniformBufferCamera(const gl::Camera& camera);
    static void UpdateUniformBufferLight(const Light& light);
    static void UpdateUniformBufferTime(float time);

private:
    static GLuint m_uboTransform;
    static GLuint m_uboMaterial;
    static GLuint m_uboCamera;
    static GLuint m_uboLight;
    static GLuint m_uboTime;

};

}   // namespace gl

#endif
