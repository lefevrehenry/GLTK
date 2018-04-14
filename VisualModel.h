#ifndef VISUALMODEL_H
#define VISUALMODEL_H

#include "Material.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Transform.h"


namespace gl {

class Mesh;

/**
 * @brief The Transform class
 */
class VisualModel
{

public:
    VisualModel(const Mesh* mesh);
    virtual ~VisualModel();

public:
    const Mesh* mesh() const;

public:
    Transform& transform();
    const Transform& transform() const;

    Material& material();
    const Material& material() const;

public:
    void draw(gl::PrimitiveMode primitiveMode) const;

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
    TexturedVisualModel(const Mesh* mesh, const Texture* texture);
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
