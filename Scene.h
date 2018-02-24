#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"

// Standard Library
#include <vector>

// Glm
#include <glm/glm.hpp>


namespace gl {

/**
 * @brief The Scene class
 */
class Scene
{

public:

    Scene();
    virtual ~Scene();

public:

    void addMesh(const std::string& filename);

    void getBbox(glm::vec3& gmin, glm::vec3& gmax) const;

    void draw(gl::DrawStyle drawStyle);

public:

    Camera& getCamera();

private:

    std::vector<const Mesh*> m_meshes;

    Camera m_camera;

};

}   // namespace gl

#endif
