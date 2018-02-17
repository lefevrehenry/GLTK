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

    enum DrawPrimitiveMode {
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
        GLuint vbo_uvcoords;
        GLuint vbo_indices;

        void loadToGPU(floatVector& vertices, floatVector& normals, floatVector& colors, floatVector& uvcoords, uintVector& indices, GLenum mode);
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
        floatVector m_uvcoord;
        uintVector m_indices;

        void draw(DrawPrimitiveMode drawMode) const;
        void drawInstanced(DrawPrimitiveMode drawMode, unsigned int instanced) const;

        MeshEntry(const aiMesh *mesh);
        virtual ~MeshEntry();
    };

protected:

    std::vector<const MeshEntry*> m_meshEntries;

    DrawPrimitiveMode drawMode;

};

}   // namespace gl

#endif
