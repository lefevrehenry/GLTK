#ifndef MESH_H
#define MESH_H

// Standard Library
#include <string>
#include <vector>

// Glm
#include <glm/glm.hpp>

// OpenGL
#include <GL/glew.h>


class aiMesh;

namespace gl {

/**
 * @brief The Mesh class
 */
class Mesh
{

public:

    typedef std::vector<float> floatVector;
    typedef std::vector<unsigned int> uintVector;

    static Mesh* fromObj(const std::string& filename);

    void draw() const;
    void drawNormal() const;

    void printInfo() const;

    void getBbox(glm::vec3 &min, glm::vec3 &max) const;

    virtual ~Mesh();

private:

    Mesh(unsigned int numMeshEntries);

private:

    struct VAO {
        GLuint id;
        GLuint vbo_vertices;
        GLuint vbo_normals;
        GLuint vbo_colors;
        GLuint vbo_indices;

        void loadToGPU(floatVector &vertices, floatVector &normals, floatVector &colors, uintVector &indices, GLenum mode);
        void free();
    };

    struct MeshEntry {
        VAO vao;

        floatVector m_vertices;
        floatVector m_normals;
        floatVector m_colors;
        uintVector m_indices;

        void draw() const;
        void drawNormal() const;

        MeshEntry(const aiMesh *mesh);
        virtual ~MeshEntry();
    };

private:

    std::vector<const MeshEntry*> m_meshEntries;

};

}   // namespace gl

#endif
