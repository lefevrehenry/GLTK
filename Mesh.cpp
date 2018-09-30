#include "Mesh.h"

#include "FileRepository.h"
#include "Message.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// Glm
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>


using namespace gl;

Mesh::Mesh() :
    m_meshEntries(0),
    m_name("")
{

}

Mesh::Mesh(const std::string& filename) :
    m_meshEntries(0),
    m_name("")
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if(!scene) {
        msg_error("Mesh") << importer.GetErrorString();
        return;
    }

    this->m_meshEntries.resize(scene->mNumMeshes);

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* aimesh = scene->mMeshes[i];
        const MeshEntry* meshEntry = new MeshEntry(aimesh);
        this->m_name = aimesh->mName.data;
        this->m_meshEntries[i] = meshEntry;
    }
}

Mesh::~Mesh()
{
    for (const MeshEntry* meshEntry : m_meshEntries) {
        delete meshEntry;
        meshEntry = nullptr;
    }
    m_meshEntries.clear();
}

Mesh* Mesh::FromFile(const std::string& filename)
{
    std::string path(filename);

    if (!helper::DataRepository.findFile(path)) {
        msg_error("Mesh") << "File " << filename << " not found";
        return nullptr;
    }

    Mesh* mesh = new Mesh(path);
    return mesh;
}

void Mesh::draw(PrimitiveMode primitiveMode) const
{
    for (unsigned int i = 0; i < m_meshEntries.size(); ++i) {
        m_meshEntries[i]->draw(primitiveMode);
    }
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

std::string Mesh::name() const
{
    return this->m_name;
}

Mesh::MeshEntry::MeshEntry(const aiMesh *mesh)
{
    if(mesh->HasPositions())
        m_vertices.resize(mesh->mNumVertices * 3);
    if(mesh->HasNormals())
        m_normals.resize(mesh->mNumVertices * 3);
    if(mesh->HasTangentsAndBitangents())
        m_tangents.resize(mesh->mNumVertices * 3);
    if(mesh->HasTangentsAndBitangents())
        m_bitangents.resize(mesh->mNumVertices * 3);
    if(mesh->HasTextureCoords(0))
        m_uvcoord.resize(mesh->mNumVertices * 2);

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

        // Vertices
        if (mesh->HasPositions()) {
            m_vertices[i * 3] = mesh->mVertices[i].x;
            m_vertices[i * 3 + 1] = mesh->mVertices[i].y;
            m_vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        // Normals
        if (mesh->HasNormals()) {
            m_normals[i * 3] = mesh->mNormals[i].x;
            m_normals[i * 3 + 1] = mesh->mNormals[i].y;
            m_normals[i * 3 + 2] = mesh->mNormals[i].z;
        }

        // Tangents and BiTangents
        if (mesh->HasTangentsAndBitangents()) {
            m_tangents[i * 3] = mesh->mTangents[i].x;
            m_tangents[i * 3 + 1] = mesh->mTangents[i].y;
            m_tangents[i * 3 + 2] = mesh->mTangents[i].z;
            m_bitangents[i * 3] = mesh->mBitangents[i].x;
            m_bitangents[i * 3 + 1] = mesh->mBitangents[i].y;
            m_bitangents[i * 3 + 2] = mesh->mBitangents[i].z;
        }

        // UV coordinates
        if (mesh->HasTextureCoords(0)) {
            unsigned int channel = 0;
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                m_uvcoord[i * 2] = mesh->mTextureCoords[channel][i].x;
                m_uvcoord[i * 2 + 1] = mesh->mTextureCoords[channel][i].y;
            }
        }
    }

    if (mesh->HasFaces()) {

        // compte le nombre de primitive
        m_numVertices = mesh->mNumVertices;
        m_numEdges = 0;
        m_numTriangles = 0;
        m_numQuads = 0;

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            if (mesh->mFaces[i].mNumIndices == 2)
                m_numEdges += 1;
            if (mesh->mFaces[i].mNumIndices == 3)
                m_numTriangles += 1;
            if (mesh->mFaces[i].mNumIndices == 4)
                m_numQuads += 1;
        }

        m_indices.resize(m_numVertices + (m_numEdges * 2) + (m_numTriangles * 3) + (m_numQuads * 4));

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            m_indices[i] = i;
        }

        unsigned int offset[4] = {0,0,0,0};
        offset[0] = 0;                                                  // offset for points
        offset[1] = m_numVertices;                                      // offset for edges
        offset[2] = m_numVertices + m_numEdges;                         // offset for triangles
        offset[3] = m_numVertices + m_numEdges + m_numTriangles;        // offset for quads

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            unsigned int k = mesh->mFaces[i].mNumIndices;
            unsigned int j = offset[k-1];
            if (k == 2) {
                m_indices[j] = mesh->mFaces[i].mIndices[0];
                m_indices[j + 1] = mesh->mFaces[i].mIndices[1];
                offset[k-1] += 2;
            } else if (k == 3) {
                m_indices[j] = mesh->mFaces[i].mIndices[0];
                m_indices[j + 1] = mesh->mFaces[i].mIndices[1];
                m_indices[j + 2] = mesh->mFaces[i].mIndices[2];
                offset[k-1] += 3;
            } else if (k == 4) {
                m_indices[j] = mesh->mFaces[i].mIndices[0];
                m_indices[j + 1] = mesh->mFaces[i].mIndices[1];
                m_indices[j + 2] = mesh->mFaces[i].mIndices[2];
                m_indices[j + 3] = mesh->mFaces[i].mIndices[3];
                offset[k-1] += 4;
            }
        }
    }

    vao.loadToGPU(m_vertices, m_normals, m_tangents, m_bitangents, m_uvcoord, m_indices, GL_STATIC_DRAW);
}

Mesh::MeshEntry::~MeshEntry()
{
    vao.free();
}

void Mesh::MeshEntry::draw(PrimitiveMode primitiveMode) const
{
    GLenum primitiveType = 0;
    unsigned int count = 0;
    unsigned int offset = 0;

    glBindVertexArray(vao.id);

    switch (primitiveMode) {
    case PrimitiveMode::POINTS:
        primitiveType = GL_POINTS;
        count = m_numVertices;
        offset = 0;

        break;
    case PrimitiveMode::LINES:
        primitiveType = GL_LINES;
        count = 2 * m_numEdges;
        offset = m_numVertices;

        break;
    case PrimitiveMode::TRIANGLES:
        primitiveType = GL_TRIANGLES;
        count = 3 * m_numTriangles;
        offset = m_numVertices + (2 * m_numEdges);

        break;
    }

    glDrawElements(primitiveType, count, GL_UNSIGNED_INT, (void*) (offset * sizeof(unsigned int)));

    glBindVertexArray(0);
}

void Mesh::VAO::loadToGPU(floatVector& vertices, floatVector& normals, floatVector& tangents, floatVector& bitangents, floatVector& uvcoords, uintVector& indices, GLenum mode) {
    // Create a vertex array object
    glGenVertexArrays(1, &id);

    // Create buffers inside the GPU memory
    glGenBuffers(1, &vbo_vertices);
//    glGenBuffers(1, &vbo_normals);
//    glGenBuffers(1, &vbo_tangents);
//    glGenBuffers(1, &vbo_bitangents);
//    glGenBuffers(1, &vbo_uvcoords);
    glGenBuffers(1, &vbo_indices);

    // Activate VAO
    glBindVertexArray(id);

    size_t verticesBufferSize = vertices.size() * sizeof(float);
    size_t normalsBufferSize = normals.size() * sizeof(float);
    size_t tangentsBufferSize = tangents.size() * sizeof(float);
    size_t bitangentsBufferSize = bitangents.size() * sizeof(float);
    size_t uvcoordsBufferSize = uvcoords.size() * sizeof(float);

    size_t bufferSize = verticesBufferSize + normalsBufferSize + tangentsBufferSize + bitangentsBufferSize + uvcoordsBufferSize;

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, mode);

    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesBufferSize, vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesBufferSize, normalsBufferSize, normals.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesBufferSize + normalsBufferSize, tangentsBufferSize, tangents.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesBufferSize + normalsBufferSize + tangentsBufferSize, bitangentsBufferSize, bitangents.data());
    glBufferSubData(GL_ARRAY_BUFFER, verticesBufferSize + normalsBufferSize + tangentsBufferSize + bitangentsBufferSize, uvcoordsBufferSize, uvcoords.data());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*) (verticesBufferSize));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, (void*) (verticesBufferSize + normalsBufferSize));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, (void*) (verticesBufferSize + normalsBufferSize + tangentsBufferSize));
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, (void*) (verticesBufferSize + normalsBufferSize + tangentsBufferSize + bitangentsBufferSize));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

//    // Store mesh positions into buffer inside the GPU memory
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), mode);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//    glEnableVertexAttribArray(0);

//    // Store mesh normals into buffer inside the GPU memory
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
//    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), mode);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*) 0);
//    glEnableVertexAttribArray(1);

//    // Store mesh tangents into buffer inside the GPU memory
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_tangents);
//    glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(float), tangents.data(), mode);
//    glVertexAttribPointer(4, 3, GL_FLOAT, GL_TRUE, 0, (void*) 0);
//    glEnableVertexAttribArray(4);

//    // Store mesh bitangents into buffer inside the GPU memory
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_bitangents);
//    glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(float), bitangents.data(), mode);
//    glVertexAttribPointer(5, 3, GL_FLOAT, GL_TRUE, 0, (void*) 0);
//    glEnableVertexAttribArray(5);

//    // Store mesh uv coords into buffer inside the GPU memory
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvcoords);
//    glBufferData(GL_ARRAY_BUFFER, uvcoords.size() * sizeof(float), uvcoords.data(), mode);
//    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//    glEnableVertexAttribArray(3);

    // Store mesh indices into buffer inside the GPU memory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), mode);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::VAO::free() {
    glDeleteBuffers(1, &vbo_vertices);
//    glDeleteBuffers(1, &vbo_normals);
//    glDeleteBuffers(1, &vbo_tangents);
//    glDeleteBuffers(1, &vbo_bitangents);
//    glDeleteBuffers(1, &vbo_uvcoords);
    glDeleteBuffers(1, &vbo_indices);
    glDeleteVertexArrays(1, &id);
}
