#ifndef GLTK_VISUALMANAGER_H
#define GLTK_VISUALMANAGER_H

#include <Camera.h>
#include <Light.h>
#include <Material.h>
#include <Transform.h>

// Glad
#include <glad/glad.h>


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
    static Transform GetTransform();
    static Material GetMaterial();
    static Camera GetCamera();
    static Light GetLight();
    static float GetTime();

public:
    static void UpdateUniformBufferTransform(const Transform& transform);
    static void UpdateUniformBufferMaterial(const Material& material);
    static void UpdateUniformBufferCamera(const Camera& camera);
    static void UpdateUniformBufferLight(const Light& light);
    static void UpdateUniformBufferTime(float time);

private:
    static GLuint m_uboTransform;
    static GLuint m_uboMaterial;
    static GLuint m_uboCamera;
    static GLuint m_uboLight;
    static GLuint m_uboTime;

    static Transform CurrentTransform;      // tracks the last data that have been uploaded on the GPU
    static Material CurrentMaterial;
    static Camera CurrentCamera;
    static Light CurrentLight;
    static float CurrentTime;

};

}   // namespace gl

#endif
