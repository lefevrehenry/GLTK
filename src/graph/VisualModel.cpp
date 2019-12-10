#include "VisualModel.h"

#include <FileRepository.h>
#include <MeshPrivate.h>
#include <Mesh.h>
#include <Message.h>
#include <ShaderProgramPrivate.h>
#include <TexturePrivate.h>

using namespace gl;
using namespace gl::helper;

VisualModel::VisualModel(std::shared_ptr<const Mesh> mesh, const Material& material) :
    m_mesh(mesh),
    m_transform(),
    m_material(material)
{

}

VisualModel::VisualModel(const std::string& filename, const Material& material) :
    m_mesh(nullptr),
    m_transform(),
    m_material(material)
{
    std::string path = filename;

    if (!DataRepository.findFile(path))
        msg_error("Mesh") << "File " << filename << " not found";
    else
        this->m_mesh.reset(new Mesh(path));
}

Transform& VisualModel::transform()
{
    return this->m_transform;
}

const Transform& VisualModel::transform() const
{
    return this->m_transform;
}

Material& VisualModel::material()
{
    return this->m_material;
}

const Material& VisualModel::material() const
{
    return this->m_material;
}

void VisualModel::getBBox(glm::vec3 &min, glm::vec3 &max) const
{
    if(!this->m_mesh)
        return;

    this->m_mesh->getBBox(min, max);
}

void VisualModel::draw() const
{
    if (this->m_mesh)
        this->m_mesh->draw();
}
