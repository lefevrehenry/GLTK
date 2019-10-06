#ifndef VISUALMODEL_H
#define VISUALMODEL_H

#include <misc/Material.h>
#include <misc/Transform.h>

// Standard Library
#include <string>


namespace gl {

class Mesh;
class VisualParam;
class Texture;

/**
 * @brief The VisualModel class
 */
class VisualModel
{

public:
    VisualModel(const Mesh* mesh, const Material& material = Material::DefaultMaterial());
    VisualModel(const std::string& filename, const Material& material = Material::DefaultMaterial());
    virtual ~VisualModel();

public:
    const Mesh* mesh() const;

public:
    Transform& transform();
    const Transform& transform() const;

    Material& material();
    const Material& material() const;

public:
    void draw(const VisualParam* param) const;

private:
    const Mesh* m_mesh;
    Transform m_transform;
    Material m_material;

};

/**
 * @brief The TexturedVisualModel class
 */
class TexturedVisualModel : public VisualModel
{

public:
    TexturedVisualModel(const std::string& filename, const Texture* texture);
    virtual ~TexturedVisualModel();

public:
    const Texture* texture() const;

//public:
//    Texture& texture();
//    const Texture& texture() const;

private:
    const Texture* m_texture;

};

}   // namespace gl

#endif
