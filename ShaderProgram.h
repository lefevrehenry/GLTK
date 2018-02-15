#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Data.h"
#include "Mesh.h"

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
        Frame
    };

    ShaderProgram();
    virtual ~ShaderProgram();

public:

    GLuint getProgramID() const;

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
        DataTracker<C, T>* data = new DataTracker<C, T>(instance, callback, dataLocation);
        m_dataList.push_back(data);

        return true;
    }

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

    std::vector<const Shader*> m_shaderList;

    std::vector< BaseData* > m_dataList;

    //helper::GLRenderOption a;

    bool m_isLinked;

};

}   // namespace gl

#endif
