#include "FileRepository.h"

#include "Helper.h"
#include "Message.h"

// Standard Library
#include <fstream>
#include <map>

// Qt
//#include <QCoreApplication>
//#include <QDir>


using namespace gl::helper;


// Definition of the extern symbol DataRepository
FileRepository gl::helper::DataRepository;

FileRepository::FileRepository() :
    m_paths(0)
{
    std::map<std::string, std::string> iniFileValues = getMapFromIniFile("../etc/config.ini");

    if (iniFileValues.find("SHARE_DIR") != iniFileValues.end()) {
        std::string shareDir = iniFileValues["SHARE_DIR"];
        addFirstPath(shareDir);
    } else {
        msg_warning("FileRepository") << "No share/ directory added";
    }
}

FileRepository::~FileRepository()
{

}

void FileRepository::addFirstPath(const std::string& path)
{
    if (path.empty())
        return;

    std::string normpath(path);
    if (normpath[normpath.size()-1] == '/')
        normpath = normpath.substr(0, normpath.size()-1);

    this->m_paths.insert(m_paths.begin(), normpath);
}

void FileRepository::addLastPath(const std::string& path)
{
    if (path.empty())
        return;

    std::string normpath(path);
    if (normpath[normpath.size()-1] == '/')
        normpath = normpath.substr(0, normpath.size()-1);

    this->m_paths.insert(m_paths.end(), normpath);
}

void FileRepository::removePath(const std::string& path)
{
    // not implemented yet
    assert(false);
}

bool FileRepository::findFile(std::string& filename)
{
    if (filename.empty())
        return false;

    std::ifstream file(filename);
    if (file.good())
        return true;

    if (filename[0] != '/') {
        for (const std::string& path : m_paths) {
            std::string fullpath = path + "/" + filename;
            std::ifstream file(fullpath);
            if (file.good()) {
                filename = fullpath;
                return true;
            }
        }
    }

    return false;
}

void FileRepository::print()
{
    for (std::string& path : m_paths) {
        msg_info("FileRepo") << path;
    }
}
