#ifndef GLTK_VISUALMODEL_H
#define GLTK_VISUALMODEL_H

#include <Material.h>
#include <Transform.h>

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
    using SPtr = std::shared_ptr<VisualModel>;
    using CSPtr = std::shared_ptr<const VisualModel>;

    using WPtr = std::weak_ptr<VisualModel>;
    using CWPtr = std::weak_ptr<const VisualModel>;

public:
    VisualModel(std::shared_ptr<const Mesh> mesh, const Material& material = Material::DefaultMaterial());
    VisualModel(const std::string& filename, const Material& material = Material::DefaultMaterial());

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
    std::shared_ptr<const Mesh> m_mesh;
    Transform                   m_transform;
    Material                    m_material;

};

}   // namespace gl

#endif
