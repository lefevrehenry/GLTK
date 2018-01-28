#ifndef HELPER_H
#define HELPER_H

#include "Message.h"

// Standard Library
#include <fstream>
#include <string>


namespace gl {

namespace helper {



static bool getStringFromFile(const std::string& filename, std::string& dest) {
    std::ifstream filestream(filename, std::ios::in);

    if(!filestream.is_open()) {
        msg_error("Error") << "File not found: " << filename;
        return false;
    }

    dest = "";
    std::string line;

    while(getline(filestream, line)) {
        dest += line + "\n";
    }

    filestream.close();

    return true;
}

//static Message& info(const char* title)
//{
//    return Message();// << "[" << title << "]: ";
//}

}   // namespace helper

namespace defaulttype {

}   // namespace defaulttype

}   // namespace gl

#endif
