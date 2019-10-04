#include <misc/Material.h>

// Glm
#include <glm/gtc/matrix_access.hpp>

using namespace gl;

Material Material::DefaultMaterial()
{
    Material material;
    material.setAmbientColor(0.3f, 0.3f, 0.2f);
    material.setDiffuseColor(0.3f, 0.5f, 0.8f);
    material.setSpecularColor(0.8f, 0.8f, 0.8f);
    material.setShininess(50.0);
    return material;
}

Material Material::Emerald()
{
    Material material;
    material.setAmbientColor(0.0215f, 0.1745f, 0.0215f);
    material.setDiffuseColor(0.07568f, 0.61424f, 0.07568f);
    material.setSpecularColor(0.633f, 0.727811f, 0.633f);
    material.setShininess(76.8f);
    return material;
}

Material Material::Jade()
{
    Material material;
    material.setAmbientColor(0.135f, 0.2225f, 0.1575f);
    material.setDiffuseColor(0.54f, 0.89f, 0.63f);
    material.setSpecularColor(0.316228f, 0.316228f, 0.316228f);
    material.setShininess(12.8f);
    return material;
}

Material Material::Obsidian()
{
    Material material;
    material.setAmbientColor(0.05375f, 0.05f, 0.06625f);
    material.setDiffuseColor(0.18275f, 0.17f, 0.22525f);
    material.setSpecularColor(0.332741f, 0.328634f, 0.346435f);
    material.setShininess(38.4f);
    return material;
}

Material Material::Pearl()
{
    Material material;
    material.setAmbientColor(0.25f, 0.20725f, 0.20725f);
    material.setDiffuseColor(1.0f, 0.829f, 0.829f);
    material.setSpecularColor(0.296648f, 0.296648f, 0.296648f);
    material.setShininess(11.264f);
    return material;
}

Material Material::Ruby()
{
    Material material;
    material.setAmbientColor(0.1745f, 0.01175f, 0.01175f);
    material.setDiffuseColor(0.61424f, 0.04136f, 0.04136f);
    material.setSpecularColor(0.727811f, 0.626959f, 0.626959f);
    material.setShininess(76.8f);
    return material;
}

Material Material::Turquoise()
{
    Material material;
    material.setAmbientColor(0.1f, 0.18725f, 0.1745f);
    material.setDiffuseColor(0.396f, 0.74151f, 0.69102f);
    material.setSpecularColor(0.297254f, 0.30829f, 0.306678f);
    material.setShininess(12.8f);
    return material;
}

Material Material::Brass()
{
    Material material;
    material.setAmbientColor(0.329412f, 0.223529f, 0.027451f);
    material.setDiffuseColor(0.780392f, 0.568627f, 0.113725f);
    material.setSpecularColor(0.992157f, 0.941176f, 0.807843f);
    material.setShininess(27.9f);
    return material;
}

Material Material::Bronze()
{
    Material material;
    material.setAmbientColor(0.2125f, 0.1275f, 0.054f);
    material.setDiffuseColor(0.714f, 0.4284f, 0.18144f);
    material.setSpecularColor(0.393548f, 0.271906f, 0.166721f);
    material.setShininess(25.6f);
    return material;
}

Material Material::Chrome()
{
    Material material;
    material.setAmbientColor(0.25f, 0.25f, 0.25f);
    material.setDiffuseColor(0.4f, 0.4f, 0.4f);
    material.setSpecularColor(0.774597f, 0.774597f, 0.774597f);
    material.setShininess(76.8f);
    return material;
}

Material Material::Copper()
{
    Material material;
    material.setAmbientColor(0.19125f, 0.0735f, 0.0225f);
    material.setDiffuseColor(0.7038f, 0.27048f, 0.0828f);
    material.setSpecularColor(0.256777f, 0.137622f, 0.086014f);
    material.setShininess(12.8f);
    return material;
}

Material Material::Gold()
{
    Material material;
    material.setAmbientColor(0.24725f, 0.1995f, 0.0745f);
    material.setDiffuseColor(0.75164f, 0.60648f, 0.22648f);
    material.setSpecularColor(0.628281f, 0.555802f, 0.366065f);
    material.setShininess(51.2f);
    return material;
}

Material Material::Silver()
{
    Material material;
    material.setAmbientColor(0.19225f, 0.19225f, 0.19225f);
    material.setDiffuseColor(0.50754f, 0.50754f, 0.50754f);
    material.setSpecularColor(0.508273f, 0.508273f, 0.508273f);
    material.setShininess(51.2f);
    return material;
}

Material::Material() :
    m_ambientColor(0.3f, 0.3f, 0.2f),
    m_diffuseColor(0.3f, 0.5f, 0.8f),
    m_specularColor(0.8f, 0.8f, 0.8f),
    m_shininess(50.0f),
    m_matrix(),
    m_isDirty(true)
{

}

Material::~Material()
{

}

const glm::mat4& Material::matrix() const
{
    if (this->m_isDirty) {
        m_matrix = glm::column(m_matrix, 0, glm::vec4(this->m_ambientColor, 1.0f));
        m_matrix = glm::column(m_matrix, 1, glm::vec4(this->m_diffuseColor, 1.0f));
        m_matrix = glm::column(m_matrix, 2, glm::vec4(this->m_specularColor, 1.0f));
        this->m_isDirty = false;
    }

    return m_matrix;
}

const glm::vec3& Material::ambientColor() const
{
    return this->m_ambientColor;
}

const glm::vec3& Material::diffuseColor() const
{
    return this->m_diffuseColor;
}

const glm::vec3& Material::specularColor() const
{
    return this->m_specularColor;
}

float Material::shininess() const
{
    return this->m_shininess;
}

void Material::setAmbientColor(float r, float g, float b)
{
    this->m_ambientColor[0] = r;
    this->m_ambientColor[1] = g;
    this->m_ambientColor[2] = b;
    this->m_isDirty = true;
}

void Material::setAmbientColor(const glm::vec3& color)
{
    this->setAmbientColor(color.r, color.g, color.b);
}

void Material::setDiffuseColor(float r, float g, float b)
{
    this->m_diffuseColor[0] = r;
    this->m_diffuseColor[1] = g;
    this->m_diffuseColor[2] = b;
    this->m_isDirty = true;
}

void Material::setDiffuseColor(const glm::vec3& color)
{
    this->setDiffuseColor(color.r, color.g, color.b);
}

void Material::setSpecularColor(float r, float g, float b)
{
    this->m_specularColor[0] = r;
    this->m_specularColor[1] = g;
    this->m_specularColor[2] = b;
    this->m_isDirty = true;
}

void Material::setSpecularColor(const glm::vec3& color)
{
    this->setSpecularColor(color.r, color.g, color.b);
}

void Material::setShininess(float shininess)
{
    this->m_shininess = shininess;
}
