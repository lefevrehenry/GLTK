#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Data.h"
#include "Mesh.h"
#include "Texture.h"

// Standard Library
#include <vector>

// OpenGL
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>


namespace gl {

class BaseData;
class Shader;

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{

public:

    enum ShaderProgramType {
        Basic,
        Normal,
        FlatShading,
        GouraudShading,
        PhongShading,
        Frame,
        HighLight,
        Texturing
    };

    // Specifies how polygons are rendered
    enum PolygonMode {
        POINT = GL_POINT,
        LINE = GL_LINE,
        FILL = GL_FILL
    };

//    struct RenderOption {
//        PolygonMode polygoneMode = FILL;
//        bool depth = true;
//    };

    ShaderProgram();
    virtual ~ShaderProgram();

public:

    GLuint getProgramID() const;

    unsigned int getNbInstance() const;

    void setNbInstance(unsigned int instance);

public:

    PolygonMode getPolygonMode() const;

    void setPolygonMode(PolygonMode polygonMode);

public:

    bool addShader(const Shader& shader);

    void link();

    bool isLinked() const;

public:

    void updateDataIfDirty();

    template< typename T >
    bool addData(const char* name, const T& value)
    {
        if (!m_isLinked)
            return false;

        int dataLocation = glGetUniformLocation(m_programId, name);

        if (dataLocation == -1) {
            msg_info("ShaderProgram") << "location of '" << name << "' not found. Data not added";
            return false;
        }

        Data<T>* data = new Data<T>(value, dataLocation);
        m_dataList.push_back(data);

        return true;
    }

    template< typename T >
    bool addData(const char* name, const Texture& value)
    {
        if (!m_isLinked)
            return false;

        int dataLocation = glGetUniformLocation(m_programId, name);

        if (dataLocation == -1) {
            msg_info("ShaderProgram") << "location of '" << name << "' not found. Data not added";
            return false;
        }

        Data<T>* data = new Data<T>(value, dataLocation);
        m_dataList.push_back(data);

        return true;
    }

    template< class C, typename T >
    bool addData(const char* name, const C* instance, const T& (C::*callback)() const)
    {
        if (!m_isLinked)
            return false;

        int dataLocation = glGetUniformLocation(m_programId, name);

        if (dataLocation == -1) {
            msg_info("ShaderProgram") << "location of '" << name << "' not found. Data not added";
            return false;
        }

        DataTracker<C, T>* data = new DataTracker<C, T>(instance, callback, dataLocation);
        m_dataList.push_back(data);

        return true;
    }

//    bool addDataTexture(const char* name, const Texture& texture)
//    {
//        if (!m_isLinked)
//            return false;

//        int dataLocation = glGetUniformLocation(m_programId, name);

//        return true;
//    }

public:

    void draw();

public:

    int attributLocation(const char* name) const;

    void setUniformValue(const char* name, float x);
    void setUniformValue(int attributLocation, float x);

    void setUniformValue(const char* name, const glm::vec2& v);
    void setUniformValue(int attributLocation, const glm::vec2& v);

    void setUniformValue(const char* name, const glm::vec3& v);
    void setUniformValue(int attributLocation, const glm::vec3& v);

    void setUniformValue(const char* name, const glm::vec4& v);
    void setUniformValue(int attributLocation, const glm::vec4& v);

    void setUniformValue(const char* name, const glm::mat2& m);
    void setUniformValue(int attributLocation, const glm::mat2& m);

    void setUniformValue(const char* name, const glm::mat3& m);
    void setUniformValue(int attributLocation, const glm::mat3& m);

    void setUniformValue(const char* name, const glm::mat4& m);
    void setUniformValue(int attributLocation, const glm::mat4& m);

private:

    GLuint m_programId;

    unsigned int m_instanced;

    PolygonMode m_polygonMode;

    std::vector<const Shader*> m_shaderList;

    std::vector< BaseData* > m_dataList;

    bool m_isLinked;

};

}   // namespace gl

#endif
