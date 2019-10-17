#include "TexturedVisualModel.h"

#include <FileRepository.h>
#include <Message.h>
#include <TexturePrivate2D.h>

using namespace gl;
using namespace gl::helper;

TexturedVisualModel::TexturedVisualModel(const std::string& filename, const std::string& textureFilename) : VisualModel(filename),
    m_texture(new TexturePrivate2D())
{
    std::string path = textureFilename;

    if (!DataRepository.findFile(path))
        msg_error("Mesh") << "File " << filename << " not found";
    else
        this->m_texture->load(path);
}

TexturedVisualModel::TexturedVisualModel(const TexturedVisualModel& other) : VisualModel (other),
    m_texture(other.m_texture)
{

}
