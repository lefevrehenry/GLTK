#ifndef VISUALMODEL_H
#define VISUALMODEL_H

#include <misc/Material.h>
#include <misc/Transform.h>

// Standard Library
#include <memory>
#include <string>


namespace gl {

class Mesh;
class VisualParam;

/**
 * @brief The VisualModel class
 */
class VisualModel
{

public:
    VisualModel(const std::string& filename, const Material& material = Material::DefaultMaterial());
    VisualModel(const VisualModel& other);

public:
    Transform& transform();
    const Transform& transform() const;

    Material& material();
    const Material& material() const;

public:
    void getBBox(glm::vec3& min, glm::vec3& max) const;

public:
    void draw(const VisualParam* param) const;

private:
    std::shared_ptr<Mesh>   m_mesh;
    Transform               m_transform;
    Material                m_material;

};

}   // namespace gl

#endif
