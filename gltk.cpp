#include "gltk.h"

// Standard Library
#include <exception>
#include <fstream>

using namespace gl;

std::map<std::string, std::string> GLTK::getMapFromIniFile(const std::string& filename)
{
    std::map<std::string, std::string> map;

    std::ifstream iniFile(filename.c_str());
    if (!iniFile.is_open())
        throw std::runtime_error("Cannot read ini file " + filename);

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
