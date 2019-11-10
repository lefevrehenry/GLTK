#ifndef GLTK_MESSAGE_H
#define GLTK_MESSAGE_H

// Standard Library
#include <iomanip>
#include <sstream>
#include <string>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace gl {

namespace helper {

/**
 * @brief The Message class
 */
class Message
{

public:
    Message();
    virtual ~Message();

    template<typename T>
    Message& operator<<(const T& x)
    {
        m_message << x;
        return *this;
    }

    Message& operator<<(const glm::vec2& x)
    {
        m_message << "(" << x[0] << "," << x[1] << ")";
        return *this;
    }

    Message& operator<<(const glm::vec3& x)
    {
        m_message << "(" << x[0] << "," << x[1] << "," << x[2] << ")";
        return *this;
    }

    Message& operator<<(const glm::vec4& x)
    {
        m_message << "(" << x[0] << "," << x[1] << "," << x[2] << "," << x[3] << ")";
        return *this;
    }

    Message& operator<<(const glm::quat& q)
    {
        m_message << "(" << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << ")";
        return *this;
    }

    Message& operator<<(const glm::mat3& m)
    {
        m_message << "Matrix 3" << std::setprecision(2);
        for (int i = 0; i < 3; ++i) {
            m_message << "\n";
            for (int j = 0; j < 3; ++j) {
                m_message << std::setw(5) << std::left << m[j][i];
            }
        }
        return *this;
    }

    Message& operator<<(const glm::mat4& m)
    {
        m_message << "Matrix 4" << std::setprecision(2);
        for (int i = 0; i < 4; ++i) {
            m_message << "\n";
            for (int j = 0; j < 4; ++j) {
                m_message << std::setw(5) << std::left << m[j][i];
            }
        }
        return *this;
    }

private:
    std::stringstream m_message;

};

}   // namespace helper

}   // namespace gl

const std::string BLACK         = std::string("\033[0;30m");
const std::string RED           = std::string("\033[0;31m");
const std::string GREEN         = std::string("\033[0;32m");
const std::string YELLOW        = std::string("\033[0;33m");
const std::string BLUE          = std::string("\033[0;34m");
const std::string PURPLE        = std::string("\033[0;35m");
const std::string CYAN          = std::string("\033[0;36m");
const std::string WHITE         = std::string("\033[0;37m");
const std::string DEFAULT_COLOR = std::string("\033[0m");

#define msg_info(x) gl::helper::Message() << GREEN << "[" << x << "] " << DEFAULT_COLOR
#define msg_warning(x) gl::helper::Message() << CYAN << "[" << x << "] " << DEFAULT_COLOR
#define msg_error(x) gl::helper::Message() << RED << "[" << x << "] " << DEFAULT_COLOR
#define msg_fatal(x) gl::helper::Message() << PURPLE << "[" << x << "] " << DEFAULT_COLOR

#endif
