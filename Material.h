#ifndef MATERIAL_H
#define MATERIAL_H

// Glm
#include <glm/glm.hpp>


namespace gl {

/**
 * @brief The Material class
 */
class Material
{

public:

    // http://devernay.free.fr/cours/opengl/materials.html
    static Material Emerald();
    static Material Jade();
    static Material Obsidian();
    static Material Pearl();
    static Material Ruby();
    static Material Turquoise();
    static Material Brass();
    static Material Bronze();
    static Material Chrome();
    static Material Copper();
    static Material Gold();
    static Material Silver();
//    static Material BlackPlastic();
//    static Material CyanPlastic();
//    static Material GreenPlastic();
//    static Material RedPlastic();
//    static Material WhitePlastic();
//    static Material YellowPlastic();
//    static Material BlackRubber();
//    static Material CyanRubber();
//    static Material GreenRubber();
//    static Material RedRubber();
//    static Material WhiteRubber();
//    static Material YellowRubber();

public:
    Material();
    virtual ~Material();

public:
    const glm::mat4& matrix() const;

public:
    const glm::vec3& ambientColor() const;
    const glm::vec3& diffuseColor() const;
    const glm::vec3& specularColor() const;
    float shininess() const;

public:
    void setAmbientColor(float r, float g, float b);
    void setAmbientColor(const glm::vec3& color);

    void setDiffuseColor(float r, float g, float b);
    void setDiffuseColor(const glm::vec3& color);

    void setSpecularColor(float r, float g, float b);
    void setSpecularColor(const glm::vec3& color);

    void setShininess(float shininess);

private:
    glm::vec3 m_ambientColor;
    glm::vec3 m_diffuseColor;
    glm::vec3 m_specularColor;
    float m_shininess;

    mutable glm::mat4 m_matrix;

    mutable bool m_isDirty;

};

}   // namespace gl

#define BLUE_MATERIAL Material()

#endif
