#ifndef MESH_H
#define MESH_H

// Standard Library
#include <string>
#include <vector>

// OpenGL
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>


class aiMesh;
class aiScene;

namespace gl {

class VisualModel;
class VisualParam;

/**
 * @brief The Mesh class
 */
class Mesh
{
    friend class VisualModel;

    typedef std::vector<float> floatVector;
    typedef std::vector<unsigned int> uintVector;

public:

    static Mesh* FromFile(const std::string& filename);

    void draw(const VisualParam* param) const;

    void getBBox(glm::vec3 &min, glm::vec3 &max) const;

    std::string name() const;

    virtual ~Mesh();

private:

    Mesh();
    Mesh(const std::string& filename);

protected:

    struct VAO {
        GLuint id;
        GLuint vbo_vertices;
//        GLuint vbo_normals;
//        GLuint vbo_tangents;
//        GLuint vbo_bitangents;
//        GLuint vbo_uvcoords;
        GLuint vbo_indices;

        void loadToGPU(floatVector& vertices, floatVector& normals, floatVector& tangents, floatVector& bitangents, floatVector& uvcoords, uintVector& indices, GLenum mode);
        void free();
    };

    struct MeshEntry {
        VAO vao;

        unsigned int m_numVertices;
        unsigned int m_numEdges;
        unsigned int m_numTriangles;
        unsigned int m_numQuads;

        floatVector m_vertices;
        floatVector m_normals;
        floatVector m_tangents;
        floatVector m_bitangents;
        floatVector m_uvcoord;
        uintVector m_indices;

        void draw(const VisualParam* param) const;

        MeshEntry(const aiMesh *mesh);
        virtual ~MeshEntry();
    };

protected:
    std::vector<const MeshEntry*>   m_meshEntries;
    std::string                     m_name;

};

}   // namespace gl

#endif
