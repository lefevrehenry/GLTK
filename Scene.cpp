#include "Scene.h"


using namespace gl;

Scene::Scene() :
    m_meshes(0),
    m_camera(Camera::Perspective)
{

}

Scene::~Scene()
{
    for (const Mesh* mesh : m_meshes) {
        delete mesh;
        mesh = nullptr;
    }
    m_meshes.clear();
}

void Scene::addMesh(const Mesh *mesh)
{
    this->m_meshes.push_back(mesh);
}

void Scene::addMesh(const std::string &filename)
{
    Mesh* mesh = Mesh::FromFile(filename);
    this->m_meshes.push_back(mesh);
}

void Scene::getBbox(glm::vec3 &gmin, glm::vec3 &gmax) const
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    gmin = glm::vec3(maxf, maxf, maxf);
    gmax = glm::vec3(minf, minf, minf);

    // query each mesh
    for (const Mesh* mesh : this->m_meshes) {
        glm::vec3 min;
        glm::vec3 max;

        mesh->getBbox(min, max);

        //update gmin
        gmin[0] = (min[0] < gmin[0] ? min[0] : gmin[0]);
        gmin[1] = (min[1] < gmin[1] ? min[1] : gmin[1]);
        gmin[2] = (min[2] < gmin[2] ? min[2] : gmin[2]);
        // update gmax
        gmax[0] = (max[0] > gmax[0] ? max[0] : gmax[0]);
        gmax[1] = (max[1] > gmax[1] ? max[1] : gmax[1]);
        gmax[2] = (max[2] > gmax[2] ? max[2] : gmax[2]);
    }
}

void Scene::draw(DrawStyle drawStyle)
{
    glPolygonMode(GL_FRONT_AND_BACK, drawStyle.polygonMode);

    for (const Mesh* mesh : this->m_meshes) {
        if (drawStyle.instanced > 1) {
            mesh->drawInstanced(drawStyle.primitiveMode, drawStyle.instanced);
        } else {
            mesh->draw(drawStyle.primitiveMode);
        }
    }
}

Camera& Scene::getCamera()
{
    return this->m_camera;
}

void Scene::fit()
{
    glm::vec3 min;
    glm::vec3 max;
    this->getBbox(min, max);

    float diagonal = glm::length(max - min);

    // view
    glm::vec3 target = (min + max) / 2.0f;
    glm::vec3 eye = target - (glm::vec3(0,0,-1) * diagonal);
    glm::vec3 up(0,1,0);
    this->m_camera.lookAt(eye, target, up);

    // projection
    float fovy = 45.0f;
    float aspect = 4.0f / 3.0f;
    float zNear = 0.2f * diagonal;
    float zFar = 2.0f * diagonal;
    this->m_camera.perspective(fovy, aspect, zNear, zFar);
}
