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
    static void Init();
    static void Clean();

public:
    static void UpdateUniformBufferTransform(const gl::Transform& transform);
    static void UpdateUniformBufferMaterial(const gl::Material& material);
    static void UpdateUniformBufferCamera(const gl::Camera& camera);

private:
    static GLuint m_uboModel;
    static GLuint m_uboCamera;

};

}   // namespace gl

#endif
