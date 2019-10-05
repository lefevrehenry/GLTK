#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <opengl/Data.h>
#include "gltk.h"
#include <statemachine/OpenGLAttribute.h>
#include <statemachine/OpenGLStateMachine.h>

// Standard Library
#include <vector>
#include <map>

// OpenGL
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>


namespace gl {

class BaseData;
class Shader;

// Specifies what kind of primives has to be rendered
enum PrimitiveType {
    POINTS = GL_POINTS,
    LINES = GL_LINES,
    TRIANGLES = GL_TRIANGLES
};

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{
    using ShaderProgramType = GLTK::ShaderProgramType;

public:
    static ShaderProgram* Create(ShaderProgramType shaderProgramType);

public:
    ShaderProgram();
    virtual ~ShaderProgram();

public:
    GLuint getProgramID() const;

public:
    unsigned int getNbInstance() const;
    void setNbInstance(unsigned int n);

public:
    PrimitiveType getPrimitiveType() const;
    void setPrimitiveType(PrimitiveType primitiveType);

public:
    template< AttributeName N >
    void set(typename OpenGL<N>::Type value)
    {
        this->m_attributeStack[N] = OpenGLAttribut<N>::Create(value);
    }

    void pushAttribute() const;
    void popAttribute() const;

public:

    bool addShader(const Shader& shader);
    void link();
    bool isLinked() const;

public:
    void bind() const;
    void unbind() const;

public:
    void updateDataIfDirty();

    template< typename T >
    bool addData(const char* name, const T& value)
    {
        if (!m_isLinked)
            return false;

        int dataLocation = glGetUniformLocation(this->m_programId, name);

        if (dataLocation == -1) {
            msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Data not added";
            return false;
        }

        Data<T>* data = new Data<T>(value, dataLocation);
        m_dataList.insert({name, data});

        return true;
    }

    template< class C, typename T >
    bool addData(const char* name, const C* instance, const T& (C::*callback)() const)
    {
        if (!m_isLinked)
            return false;

        int dataLocation = glGetUniformLocation(m_programId, name);

        if (dataLocation == -1) {
            msg_warning("ShaderProgram") << "uniform location '" << name << "' not found. Data not added";
            return false;
        }

        DataTracker<C, T>* data = new DataTracker<C, T>(instance, callback, dataLocation);
        m_dataList.insert({name, data});

        return true;
    }

public:
    template< typename T >
    Data<T>* getDataByName(const char* name)
    {
        for (auto it = m_dataList.begin(); it != m_dataList.end(); ++it) {
            if (it->first == name) {
                return dynamic_cast< Data<T>* >(it->second);
            }
        }

        return nullptr;
    }

public:
    bool addUniformBlock(const char* name, unsigned int binding_index);

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
    std::vector< const Shader* > m_shaderList;
    std::map< const char*, BaseData* > m_dataList;

    bool m_isLinked;

    unsigned int m_nbInstance;
    PrimitiveType m_primitiveType;

    std::map< AttributeName, BaseOpenGLAttribut::SPtr > m_attributeStack;

};

}   // namespace gl

#endif
