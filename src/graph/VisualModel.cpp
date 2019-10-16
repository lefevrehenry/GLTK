#include "VisualModel.h"

#include <helper/FileRepository.h>
#include <opengl/MeshPrivate.h>
#include <helper/Message.h>
#include <opengl/ShaderProgramPrivate.h>
#include <opengl/Texture.h>

using namespace gl;
using namespace gl::helper;

VisualModel::VisualModel(const std::string& filename, const Material& material) :
    m_mesh(nullptr),
    m_transform(),
    m_material(material)
{
    std::string path = filename;

    if (!DataRepository.findFile(path))
        msg_error("Mesh") << "File " << filename << " not found";
    else
        this->m_mesh.reset(new MeshPrivate(path));
}

VisualModel::VisualModel(const VisualModel& other) :
    m_mesh(other.m_mesh),
    m_transform(other.m_transform),
    m_material(other.m_material)
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

void VisualModel::draw(const VisualParam* param) const
{
    if (this->m_mesh)
        this->m_mesh->draw(param);
}
