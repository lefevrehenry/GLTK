#include "Mesh.h"

#include <MeshPrivate.h>

using namespace gl;

Mesh::Mesh(const std::string& filename) :
    m_meshPrivate(nullptr)
{
    this->m_meshPrivate.reset(MeshPrivate::FromFile(filename));
}

void Mesh::getBBox(glm::vec3 &min, glm::vec3 &max) const
{
    if(!this->m_meshPrivate)
        return;

    this->m_meshPrivate->getBBox(min, max);
}

void Mesh::draw() const
{
    if(!this->m_meshPrivate)
        return;

    this->m_meshPrivate->draw();
}

