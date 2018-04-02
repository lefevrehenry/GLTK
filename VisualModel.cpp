#include "VisualModel.h"

#include "Mesh.h"


using namespace gl;

VisualModel::VisualModel() :
    m_mesh(nullptr),
    m_transform()
{

}

VisualModel::VisualModel(const Mesh *mesh) :
    m_mesh(mesh),
    m_transform()
{

}

VisualModel::~VisualModel()
{

}

Transform& VisualModel::transform()
{
    return this->m_transform;
}

const Transform& VisualModel::transform() const
{
    return this->m_transform;
}

void VisualModel::draw(PrimitiveMode primitiveMode) const
{
    if (this->m_mesh)
        this->m_mesh->draw(primitiveMode);
}
