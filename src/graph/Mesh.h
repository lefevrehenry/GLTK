#ifndef MESH_H
#define MESH_H

// Standard Library
#include <memory>
#include <string>

// Glm
#include <glm/glm.hpp>


namespace gl {

class MeshPrivate;
class VisualParam;

/**
 * @brief The Mesh class
 */
class Mesh
{

//public:
//    using SPtr = std::shared_ptr<const Mesh>;

public:
    Mesh(const std::string& filename);

public:
    void getBBox(glm::vec3& min, glm::vec3& max) const;

public:
    void draw(const VisualParam* param) const;

private:
    std::shared_ptr<MeshPrivate>    m_meshPrivate;

};

}   // namespace gl

#endif
