#ifndef GLTK_FILEREPOSITORY_H
#define GLTK_FILEREPOSITORY_H

// Standard Library
#include <string>
#include <list>


namespace gl {

namespace helper {

/**
 * @brief The FileRepository class
 */
class FileRepository
{

public:
    FileRepository();
    virtual ~FileRepository();

public:
    void addFirstPath(const std::string& path);
    void addLastPath(const std::string& path);
    void removePath(const std::string& path);

public:
    bool findFile(std::string& filename);

private:
    std::list< std::string > m_paths;

};

// extern definition of a FileRepository
extern FileRepository DataRepository;

}   // namespace helper

}   // namespace gl


#endif
