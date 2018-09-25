#include "VisualManager.h"

#include <glm/gtc/type_ptr.hpp>

using namespace gl;

GLuint VisualManager::m_uboModel = 0;
GLuint VisualManager::m_uboCamera = 0;

void VisualManager::Init()
{
    // Uniform Buffer Object Model
    glGenBuffers(1, &m_uboModel);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboModel);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferTransform(Transform());
    VisualManager::UpdateUniformBufferMaterial(Material());

    // Bind l'uniform buffer object a l'index 1 dans la table de liaison d'OpenGL
    GLuint binding_uboModel_point_index = 1;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboModel_point_index, m_uboModel);

    // Uniform Buffer Object Camera
    glGenBuffers(1, &m_uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferCamera(Camera());

    // Bind l'uniform buffer object a l'index 2 dans la table de liaison d'OpenGL
    GLuint binding_uboCamera_point_index = 2;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboCamera_point_index, m_uboCamera);
}

void VisualManager::Clean()
{
    glDeleteBuffers(1, &m_uboModel);
    glDeleteBuffers(1, &m_uboCamera);
}

void VisualManager::UpdateUniformBufferTransform(const Transform& transform)
{
    const glm::mat4& matrix = transform.matrix();

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboModel);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(matrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferMaterial(const Material& material)
{
    const glm::mat4& matrix = material.matrix();
    float shininess = material.shininess();

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboModel);
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(float), &shininess);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferCamera(const Camera& camera)
{
    const glm::mat4& view = camera.view();
    const glm::mat4& projection = camera.projection();
    const glm::mat4& ProjViewMatrix = camera.mvp();
    const glm::mat4& NormalMatrix = glm::mat4(camera.normal());

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboCamera);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ProjViewMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(NormalMatrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
