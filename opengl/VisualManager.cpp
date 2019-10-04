#include <opengl/VisualManager.h>

#include <glm/gtc/type_ptr.hpp>

using namespace gl;

GLuint VisualManager::m_uboTransform = 0;
GLuint VisualManager::m_uboMaterial = 0;
GLuint VisualManager::m_uboCamera = 0;
GLuint VisualManager::m_uboLight = 0;
GLuint VisualManager::m_uboTime = 0;

void VisualManager::Init()
{
    // Uniform Buffer Object Transform
    glGenBuffers(1, &m_uboTransform);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboTransform);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferTransform(Transform());

    // Bind l'uniform buffer object a l'index 'TransformIndex' dans la table de liaison d'OpenGL
    GLuint binding_uboTransform_point_index = TransformIndex;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboTransform_point_index, m_uboTransform);

    // Uniform Buffer Object Material
    glGenBuffers(1, &m_uboMaterial);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMaterial);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) + sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Bind l'uniform buffer object a l'index 'MaterialIndex' dans la table de liaison d'OpenGL
    GLuint binding_uboMaterial_point_index = MaterialIndex;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboMaterial_point_index, m_uboMaterial);

    VisualManager::UpdateUniformBufferMaterial(Material());

    // Uniform Buffer Object Camera
    glGenBuffers(1, &m_uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferCamera(Camera());

    // Bind l'uniform buffer object a l'index 'CameraIndex' dans la table de liaison d'OpenGL
    GLuint binding_uboCamera_point_index = CameraIndex;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboCamera_point_index, m_uboCamera);

    // Uniform Buffer Object Light
    glGenBuffers(1, &m_uboLight);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLight);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferLight(Light());

    // Bind l'uniform buffer object a l'index 'LightIndex' dans la table de liaison d'OpenGL
    GLuint binding_uboLight_point_index = LightIndex;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboLight_point_index, m_uboLight);

    // Uniform Buffer Object Time
    glGenBuffers(1, &m_uboTime);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboTime);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    VisualManager::UpdateUniformBufferTime(0.f);

    // Bind l'uniform buffer object a l'index 'TimeIndex' dans la table de liaison d'OpenGL
    GLuint binding_uboTime_point_index = TimeIndex;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboTime_point_index, m_uboTime);
}

void VisualManager::Clean()
{
    glDeleteBuffers(1, &m_uboTransform);
    glDeleteBuffers(1, &m_uboMaterial);
    glDeleteBuffers(1, &m_uboCamera);
    glDeleteBuffers(1, &m_uboLight);
    glDeleteBuffers(1, &m_uboTime);
}

void VisualManager::UpdateUniformBufferTransform(const Transform& transform)
{
    const glm::mat4& ModelMatrix = transform.matrix();
    const glm::mat4& ModelNormalMatrix = glm::transpose(glm::inverse(ModelMatrix));

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboTransform);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ModelMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ModelNormalMatrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferMaterial(const Material& material)
{
    const glm::mat4& matrix = material.matrix();
    float shininess = material.shininess();

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMaterial);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(matrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(float), &shininess);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferCamera(const Camera& camera)
{
    const glm::mat4& View = camera.view();
    const glm::mat4& Projection = camera.projection();
    const glm::mat4& ProjViewMatrix = camera.mvp();
    const glm::mat4& NormalMatrix = glm::mat4(camera.normal());

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboCamera);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(View));
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(Projection));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ProjViewMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(NormalMatrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferLight(const Light& light)
{
    const glm::mat4& matrix = glm::mat4(light.matrix());

    glBindBuffer(GL_UNIFORM_BUFFER, m_uboLight);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(matrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::UpdateUniformBufferTime(float time)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboTime);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &time);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
