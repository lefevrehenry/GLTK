#ifndef VISUALMODEL_H
#define VISUALMODEL_H

#include "Material.h"
#include "ShaderProgram.h"
#include "Transform.h"


namespace gl {

class Mesh;

/**
 * @brief The Transform class
 */
class VisualModel
{

public:
    VisualModel();
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

}   // namespace gl

#endif
