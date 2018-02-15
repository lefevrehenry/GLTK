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
class aiScene;

namespace gl {

/**
 * @brief The Mesh class
 */
class Mesh
{

public:

    typedef std::vector<float> floatVector;
    typedef std::vector<unsigned int> uintVector;

    enum DrawPrimitive {
        POINTS,
        EDGES,
        TRIANGLES
    };

public:

    static Mesh* FromFile(const std::string& filename);

    virtual void draw() const;

    virtual void drawInstanced(unsigned int instanced) const;

    virtual void getBbox(glm::vec3 &min, glm::vec3 &max) const;

    virtual ~Mesh();

protected:

    Mesh();
    Mesh(const std::string& filename);

protected:

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

        unsigned int m_numVertices;
        unsigned int m_numEdges;
        unsigned int m_numTriangles;
        unsigned int m_numQuads;

        floatVector m_vertices;
        floatVector m_normals;
        floatVector m_colors;
        uintVector m_indices;

        void draw(DrawPrimitive drawPrimitive) const;
        void drawInstanced(DrawPrimitive drawPrimitive, unsigned int instanced) const;

        MeshEntry(const aiMesh *mesh);
        virtual ~MeshEntry();
    };

protected:

    std::vector<const MeshEntry*> m_meshEntries;

};

}   // namespace gl

#endif
