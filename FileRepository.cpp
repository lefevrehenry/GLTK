#include "FileRepository.h"

#include "Message.h"

// Qt
#include <QCoreApplication>
#include <QDir>


using namespace gl::helper;

// Definition of the extern symbol DataRepository
FileRepository gl::helper::DataRepository;

FileRepository::FileRepository() :
    m_paths(0)
{

}

FileRepository::~FileRepository()
{

}

void FileRepository::addFirstPath(const std::string &path)
{
    this->m_paths.insert(m_paths.begin(), path);
}

void FileRepository::addLastPath(const std::string &path)
{
    this->m_paths.insert(m_paths.end(), path);
}

void FileRepository::removePath(const std::string &path)
{

}

bool FileRepository::findFile(std::string &filename)
{

}

void FileRepository::print()
{
    for (std::string& path : m_paths) {
        msg_info("FileRepo") << path;
    }
}
