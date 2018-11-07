#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Data.h"

// Standard Library
#include <vector>
#include <map>
#include <stack>

// OpenGL
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>


namespace gl {

class BaseData;
class Shader;

// Specifies what kind of primives has to be rendered
enum PrimitiveMode {
    POINTS = GL_POINTS,
    LINES = GL_LINES,
    TRIANGLES = GL_TRIANGLES
};

/**
 * @brief The OpenGLState class
 */
class OpenGLState
{

public:

    enum OpenGLAttribute {
        DepthMask,
        DepthTest,
        DepthFunc,
        CullFace
    };

public:
    static void Push(OpenGLAttribute attribute, unsigned int value);
    static void Pop(OpenGLAttribute attribute);

private:
    static std::map<OpenGLAttribute, std::stack<unsigned int> > OpenGLStateAttribute;

};

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{

    typedef OpenGLState::OpenGLAttribute OpenGLAttribute;

public:

    enum ShaderProgramType {
        Basic,
        Normal,
        FlatShading,
        GouraudShading,
        PhongShading,
        Frame,
        HighLight,
        BasicTexturing,
        Texturing,
        TangentSpace,
        Picking,
        OutLine,
        MatCap,
        VaoQuad,
        Deferred,
        ShadowMapping,
        NormalMapping,
        CubeMap,
        EnvironmentMapping
    };

public:

    ShaderProgram();
    virtual ~ShaderProgram();

public:

    GLuint getProgramID() const;

public:

    unsigned int getNbInstance() const;
    void setNbInstance(unsigned int n);

public:

    PrimitiveMode getPrimitiveMode() const;
    void setPrimitiveMode(PrimitiveMode primitiveMode);

public:

    void set(OpenGLAttribute attribute, unsigned int value);
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
    PrimitiveMode m_primitiveMode;

    mutable std::map< OpenGLState::OpenGLAttribute, unsigned int > m_attributeStack;

};

}   // namespace gl

#endif
