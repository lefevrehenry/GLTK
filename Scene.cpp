#include "Scene.h"

#include "VisualModel.h"

using namespace gl;

Scene::Scene() :
    m_rootNode(),
    m_camera(Camera::Perspective),
    m_visualManager()
{

}

Scene::~Scene()
{

}

Node* Scene::root()
{
    return &m_rootNode;
}

Camera* Scene::camera()
{
    return &m_camera;
}

void Scene::draw(Node* node)
{
    this->m_visualManager.draw(node);
}

void Scene::draw()
{
    this->draw(root());
}

//void Scene::addMesh(const Mesh *mesh)
//{
//    this->m_meshes.push_back(mesh);
//}

//void Scene::addMesh(const std::string &filename)
//{
//    Mesh* mesh = Mesh::FromFile(filename);
//    this->m_meshes.push_back(mesh);
//}

void Scene::getBbox(glm::vec3& min, glm::vec3& max) const
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    min = glm::vec3(maxf, maxf, maxf);
    max = glm::vec3(minf, minf, minf);

//    // query each mesh
//    for (const Mesh* mesh : this->m_meshes) {
//        glm::vec3 min;
//        glm::vec3 max;

//        mesh->getBbox(min, max);

//        //update gmin
//        gmin[0] = (min[0] < gmin[0] ? min[0] : gmin[0]);
//        gmin[1] = (min[1] < gmin[1] ? min[1] : gmin[1]);
//        gmin[2] = (min[2] < gmin[2] ? min[2] : gmin[2]);
//        // update gmax
//        gmax[0] = (max[0] > gmax[0] ? max[0] : gmax[0]);
//        gmax[1] = (max[1] > gmax[1] ? max[1] : gmax[1]);
//        gmax[2] = (max[2] > gmax[2] ? max[2] : gmax[2]);
//    }
}

//void Scene::draw(DrawStyle drawStyle)
//{
//    glPolygonMode(GL_FRONT_AND_BACK, drawStyle.polygonMode);

//    for (const Mesh* mesh : this->m_meshes) {
//        if (drawStyle.instanced > 1) {
//            mesh->drawInstanced(drawStyle.primitiveMode, drawStyle.instanced);
//        } else {
//            mesh->draw(drawStyle.primitiveMode);
//        }
//    }
//}

void Scene::fitCamera()
{
    float d = 5;
    glm::vec3 min(-d,-d,-d);
    glm::vec3 max(d,d,d);
    //this->getBbox(min, max);

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

