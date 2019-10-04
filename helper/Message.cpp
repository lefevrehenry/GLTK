#include <helper/Message.h>

// Standard Library
#include <iostream>


using namespace gl;
using namespace gl::helper;

Message::Message() :
    m_message()
{

}

Message::~Message()
{
    std::cout << m_message.str() << std::endl;
}
