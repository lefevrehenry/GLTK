#ifndef MESSAGE_H
#define MESSAGE_H

// Standard Library
#include <sstream>
#include <string>

// Glm
#include <glm/glm.hpp>

// Qt
#include <QString>


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

    Message& operator<<(const QString& x)
    {
        m_message << x.toStdString();
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
