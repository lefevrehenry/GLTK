#ifndef HELPER_H
#define HELPER_H

#include "Message.h"

// Standard Library
#include <fstream>
#include <map>
#include <string>

namespace gl {

namespace helper {

static std::map<std::string, std::string> getMapFromIniFile(const std::string& filename)
{
    std::map<std::string, std::string> map;

    std::ifstream iniFile(filename.c_str());
    if (!iniFile.is_open()) {
        msg_error("Helper") << "Cannot read ini file " << filename;
    }

    std::string line;
    while (std::getline(iniFile, line)) {
        size_t equalPos = line.find_first_of('=');
        if (equalPos != std::string::npos) {
            const std::string key = line.substr(0, equalPos);
            const std::string value = line.substr(equalPos + 1, std::string::npos);
            map[key] = value;
        }
    }

    return map;
}

static bool getStringFromFile(const std::string& filename, std::string& dest)
{
    std::ifstream filestream(filename, std::ios::in);

    if(!filestream.is_open()) {
        msg_error("Helper") << "File " << filename << " not found";
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

}   // namespace helper

}   // namespace gl

#endif
