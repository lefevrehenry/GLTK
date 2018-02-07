#include "Mesh.h"

#include "Message.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


using namespace gl;

Mesh::Mesh(unsigned int numMeshEntries) :
    m_meshEntries(numMeshEntries)
{
}

Mesh::~Mesh()
{
    for (unsigned int i = 0; i < m_meshEntries.size(); ++i) {
        delete m_meshEntries[i];
    }
}

Mesh* Mesh::fromObj(const std::string& filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals);
//    const aiScene *scene = importer.ReadFile(filename, aiProcess_GenNormals);

    if(!scene) {
        msg_error("Mesh") << importer.GetErrorString();
        return nullptr;
    }

    Mesh* mesh = new Mesh(scene->mNumMeshes);

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* aimesh = scene->mMeshes[i];
        const MeshEntry* meshEntry = new MeshEntry(aimesh);
        mesh->m_meshEntries[i] = meshEntry;
    }

    return mesh;
}

void Mesh::draw() const
{
    for (unsigned int i = 0; i < m_meshEntries.size(); ++i) {
        m_meshEntries[i]->draw();
    }
}

void Mesh::printInfo() const
{
    unsigned int nbVertices = 0;
    unsigned int nbTriangles = 0;
    unsigned int nbQuads = 0;
    for (unsigned int i = 0; i < m_meshEntries.size(); ++i) {
        nbVertices += m_meshEntries[i]->m_vertices.size() / 3.0;
    }
    msg_info("Mesh") << nbVertices << "vertices loaded";
}

void Mesh::getBbox(glm::vec3 &min, glm::vec3 &max) const
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    min = glm::vec3(maxf, maxf, maxf);
    max = glm::vec3(minf, minf, minf);

    // query each meshEntry
    for (unsigned int x = 0; x < m_meshEntries.size(); ++x) {
        const floatVector& vertices = m_meshEntries[x]->m_vertices;
        unsigned int nbVertices = vertices.size() / 3.0;
        // loop over all vertices
        for (unsigned int i = 0; i < nbVertices; ++i) {
            float vx = vertices[i * 3];
            float vy = vertices[i * 3 + 1];
            float vz = vertices[i * 3 + 2];
            //update min
            min[0] = (vx < min[0] ? vx : min[0]);
            min[1] = (vy < min[1] ? vy : min[1]);
            min[2] = (vz < min[2] ? vz : min[2]);
            // update max
            max[0] = (vx > max[0] ? vx : max[0]);
            max[1] = (vy > max[1] ? vy : max[1]);
            max[2] = (vz > max[2] ? vz : max[2]);
        }
    }
}

Mesh::MeshEntry::MeshEntry(const aiMesh *mesh)
{
    msg_info("MeshLoader") << mesh->mName.data << " imported";

    if (mesh->HasPositions()) {
        m_vertices.resize(mesh->mNumVertices * 3);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            m_vertices[i * 3] = mesh->mVertices[i].x;
            m_vertices[i * 3 + 1] = mesh->mVertices[i].y;
            m_vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }
    }

    if (mesh->HasNormals()) {
        m_normals.resize(mesh->mNumVertices * 3);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            m_normals[i * 3] = mesh->mNormals[i].x;
            m_normals[i * 3 + 1] = mesh->mNormals[i].y;
            m_normals[i * 3 + 2] = mesh->mNormals[i].z;
        }
    }

    if (mesh->HasPositions()) {
        m_colors.resize(mesh->mNumVertices * 3);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            m_colors[i * 3] = 0.8f;
            m_colors[i * 3 + 1] = 0.8f;
            m_colors[i * 3 + 2] = 0.8f;
        }
    }

    if (mesh->HasFaces()) {
        m_indices.resize(mesh->mNumFaces * 3);
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            if (mesh->mFaces[i].mNumIndices != 3)
                continue;
            m_indices[3 * i] = mesh->mFaces[i].mIndices[0];
            m_indices[3 * i + 1] = mesh->mFaces[i].mIndices[1];
            m_indices[3 * i + 2] = mesh->mFaces[i].mIndices[2];
        }
    }

    vao.loadToGPU(m_vertices, m_normals, m_colors, m_indices, GL_STATIC_DRAW);
}

Mesh::MeshEntry::~MeshEntry()
{
    vao.free();
}

void Mesh::MeshEntry::draw() const
{
    glBindVertexArray(vao.id);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::VAO::loadToGPU(floatVector &vertices, floatVector &normals, floatVector &colors, uintVector &indices, GLenum mode) {
    // Create a vertex array object
    glGenVertexArrays(1, &id);

    // Create buffers inside the GPU memory
    glGenBuffers(1, &vbo_vertices);
    glGenBuffers(1, &vbo_normals);
    glGenBuffers(1, &vbo_colors);
    glGenBuffers(1, &vbo_indices);

    // Activate VAO
    glBindVertexArray(id);

    // Store mesh positions into buffer inside the GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), mode);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(0);

    // Store mesh normals into buffer inside the GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), mode);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*) 0);
    glEnableVertexAttribArray(1);

    // Store mesh colors into buffer inside the GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), mode);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(2);

    // Store mesh indices into buffer inside the GPU memory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), mode);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::VAO::free() {
    glDeleteBuffers(1, &vbo_vertices);
    glDeleteBuffers(1, &vbo_normals);
    glDeleteBuffers(1, &vbo_colors);
    glDeleteBuffers(1, &vbo_indices);
    glDeleteVertexArrays(1, &id);
}
