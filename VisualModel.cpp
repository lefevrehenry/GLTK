#include "VisualModel.h"

#include "FileRepository.h"
#include "Mesh.h"


using namespace gl;
using namespace gl::helper;

//VisualModel::VisualModel() :
//    m_mesh(nullptr),
//    m_transform(),
//    m_material()
//{

//}

VisualModel::VisualModel(const std::string& filename, const Material& material) :
    m_mesh(nullptr),
    m_transform(),
    m_material(material)
{
    std::string path = filename;

    if (!DataRepository.findFile(path))
        msg_error("Mesh") << "File " << filename << " not found";
    else
        this->m_mesh = new Mesh(path);
}

VisualModel::~VisualModel()
{
    delete m_mesh;
    m_mesh = nullptr;
}

const Mesh* VisualModel::mesh() const
{
    return this->m_mesh;
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

void VisualModel::draw(PrimitiveMode primitiveMode) const
{
    if (this->m_mesh)
        this->m_mesh->draw(primitiveMode);
}

TexturedVisualModel::TexturedVisualModel(const std::string& filename, const Texture* texture) : VisualModel(filename),
    m_texture(texture)
{

}

TexturedVisualModel::~TexturedVisualModel()
{

}

const Texture* TexturedVisualModel::texture() const
{
    return this->m_texture;
}

//Texture& TexturedVisualModel::texture()
//{
//    return this->m_texture;
//}

//const Texture& TexturedVisualModel::texture() const
//{
//    return this->m_texture;
//}
