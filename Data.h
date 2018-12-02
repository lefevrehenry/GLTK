#ifndef DATA_H
#define DATA_H

#include "Camera.h"
#include "Message.h"
#include "Texture.h"

// Glew
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace gl {

/**
 * @brief The BaseData class
 */
class BaseData
{

public:

    BaseData(int dataLocation);    
    virtual ~BaseData();

public:

    /**
     * @brief tell wether the data is up-to-date in the shader
     * @return true if data value need to be updated
     */
    virtual bool isDirty() const;

    /**
     * @brief call update function if data value is not up-to-date
     * at the end dirty flag is cleaned
     */
    virtual void updateIfDirty();

protected:

    /**
     * @brief update the data value to the shader
     */
    virtual void update() = 0;

protected:

    int m_dataLocation;
    bool m_dirty;

};

/**
 * @brief The Data class
 */
template< typename T >
class Data : public BaseData
{

public:
    Data(const T& value, int dataLocation) : BaseData(dataLocation),
        m_value(value)
    {
    }

    Data(int dataLocation) : BaseData(dataLocation),
        m_value()
    {
    }

    virtual ~Data()
    {
    }

public:

    /**
     * @brief set the value contained by the data
     * @param the new value of the data
     */
    virtual void setValue(const T& value)
    {
        this->m_value = value;
        this->m_dirty = true;
    }

protected:

    virtual void update()
    {
        msg_error("Data") << "update function not specialized for the given template";
    }

protected:
    T m_value;

};

template<> inline void Data<float>::update()
{
    glUniform1f(this->m_dataLocation, this->m_value);
}

template<> inline void Data<int>::update()
{
    glUniform1i(this->m_dataLocation, this->m_value);
}

template<> inline void Data<unsigned int>::update()
{
    glUniform1ui(this->m_dataLocation, this->m_value);
}

template<> inline void Data<glm::vec2>::update()
{
    glUniform2fv(this->m_dataLocation, 1, glm::value_ptr(this->m_value));
}

template<> inline void Data<glm::vec3>::update()
{
    glUniform3fv(this->m_dataLocation, 1, glm::value_ptr(this->m_value));
}

template<> inline void Data<glm::vec4>::update()
{
    glUniform4fv(this->m_dataLocation, 1, glm::value_ptr(this->m_value));
}

template<> inline void Data<glm::mat2>::update()
{
    glUniformMatrix2fv(this->m_dataLocation, 1, GL_FALSE, glm::value_ptr(this->m_value));
}

template<> inline void Data<glm::mat3>::update()
{
    glUniformMatrix3fv(this->m_dataLocation, 1, GL_FALSE, glm::value_ptr(this->m_value));
}

template<> inline void Data<glm::mat4>::update()
{
    glUniformMatrix4fv(this->m_dataLocation, 1, GL_FALSE, glm::value_ptr(this->m_value));
}

template<> inline void Data<Texture>::update()
{
    unsigned short unit = this->m_value.getTextureUnit();

    this->m_value.bind();

    glUniform1i(this->m_dataLocation, unit);
}

template<> inline void Data<CubeMapTexture>::update()
{
    unsigned short unit = this->m_value.getTextureUnit();

    this->m_value.bind();

    glUniform1i(this->m_dataLocation, unit);
}

/**
 * @brief The DataTracker class
 */
template< class C, typename T >
class DataTracker : public Data<T>
{

public:
    DataTracker(const C* instance, const T& (C::*callback)() const, int dataLocation) : Data<T>(dataLocation),
        m_instance(instance),
        getValue(callback)
    {
    }

public:

    virtual void updateIfDirty()
    {
        const T& newValue = (this->m_instance->*getValue)();

        if (this->m_value != newValue)
            this->setValue(newValue);

        Data<T>::updateIfDirty();
    }

protected:
    const C* m_instance;
    const T& (C::*getValue)() const;

};

}   // namespace

#endif
