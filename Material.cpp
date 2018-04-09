#include "Material.h"

// Glm
#include <glm/gtc/matrix_access.hpp>


using namespace gl;

Material Material::Emerald()
{
    Material material;
    material.setAmbientColor(0.0215, 0.1745, 0.0215);
    material.setDiffuseColor(0.07568, 0.61424, 0.07568);
    material.setSpecularColor(0.633, 0.727811, 0.633);
    material.setShininess(76.8);
    return material;
}

Material Material::Jade()
{
    Material material;
    material.setAmbientColor(0.135, 0.2225, 0.1575);
    material.setDiffuseColor(0.54, 0.89, 0.63);
    material.setSpecularColor(0.316228, 0.316228, 0.316228);
    material.setShininess(12.8);
    return material;
}

Material Material::Obsidian()
{
    Material material;
    material.setAmbientColor(0.05375, 0.05, 0.06625);
    material.setDiffuseColor(0.18275, 0.17, 0.22525);
    material.setSpecularColor(0.332741, 0.328634, 0.346435);
    material.setShininess(38.4);
    return material;
}

Material Material::Pearl()
{
    Material material;
    material.setAmbientColor(0.25, 0.20725, 0.20725);
    material.setDiffuseColor(1, 0.829, 0.829);
    material.setSpecularColor(0.296648, 0.296648, 0.296648);
    material.setShininess(11.264);
    return material;
}

Material Material::Ruby()
{
    Material material;
    material.setAmbientColor(0.1745, 0.01175, 0.01175);
    material.setDiffuseColor(0.61424, 0.04136, 0.04136);
    material.setSpecularColor(0.727811, 0.626959, 0.626959);
    material.setShininess(76.8);
    return material;
}

Material Material::Turquoise()
{
    Material material;
    material.setAmbientColor(0.1, 0.18725, 0.1745);
    material.setDiffuseColor(0.396, 0.74151, 0.69102);
    material.setSpecularColor(0.297254, 0.30829, 0.306678);
    material.setShininess(12.8);
    return material;
}

Material Material::Brass()
{
    Material material;
    material.setAmbientColor(0.329412, 0.223529, 0.027451);
    material.setDiffuseColor(0.780392, 0.568627, 0.113725);
    material.setSpecularColor(0.992157, 0.941176, 0.807843);
    material.setShininess(27.9);
    return material;
}

Material Material::Bronze()
{
    Material material;
    material.setAmbientColor(0.2125, 0.1275, 0.054);
    material.setDiffuseColor(0.714, 0.4284, 0.18144);
    material.setSpecularColor(0.393548, 0.271906, 0.166721);
    material.setShininess(25.6);
    return material;
}

Material Material::Chrome()
{
    Material material;
    material.setAmbientColor(0.25, 0.25, 0.25);
    material.setDiffuseColor(0.4, 0.4, 0.4);
    material.setSpecularColor(0.774597, 0.774597, 0.774597);
    material.setShininess(76.8);
    return material;
}

Material Material::Copper()
{
    Material material;
    material.setAmbientColor(0.19125, 0.0735, 0.0225);
    material.setDiffuseColor(0.7038, 0.27048, 0.0828);
    material.setSpecularColor(0.256777, 0.137622, 0.086014);
    material.setShininess(12.8);
    return material;
}

Material Material::Gold()
{
    Material material;
    material.setAmbientColor(0.24725, 0.1995, 0.0745);
    material.setDiffuseColor(0.75164, 0.60648, 0.22648);
    material.setSpecularColor(0.628281, 0.555802, 0.366065);
    material.setShininess(51.2);
    return material;
}

Material Material::Silver()
{
    Material material;
    material.setAmbientColor(0.19225, 0.19225, 0.19225);
    material.setDiffuseColor(0.50754, 0.50754, 0.50754);
    material.setSpecularColor(0.508273, 0.508273, 0.508273);
    material.setShininess(51.2);
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
