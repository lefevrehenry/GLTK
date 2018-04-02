#ifndef VISUALMODEL_H
#define VISUALMODEL_H

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
    Transform& transform();
    const Transform& transform() const;

public:
    void draw(gl::PrimitiveMode primitiveMode) const;

private:
    const Mesh* m_mesh;
    Transform m_transform;

};

}   // namespace gl

#endif
