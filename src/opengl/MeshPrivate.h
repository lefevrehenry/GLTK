#ifndef GLTK_MESHPRIVATE_H
#define GLTK_MESHPRIVATE_H

// Standard Library
#include <string>
#include <vector>

// Glad
#include <glad/glad.h>

// Glm
#include <glm/glm.hpp>


class aiMesh;
class aiScene;

namespace gl {

class VisualParam;

/**
 * @brief The MeshPrivate class
 */
class MeshPrivate
{
    typedef std::vector<float> floatVector;
    typedef std::vector<unsigned int> uintVector;

public:

    static MeshPrivate* FromFile(const std::string& filename);

    void draw(const VisualParam* param) const;

    void getBBox(glm::vec3& min, glm::vec3& max) const;

    std::string name() const;

    virtual ~MeshPrivate();

private:

    MeshPrivate();
    MeshPrivate(const std::string& filename);

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
