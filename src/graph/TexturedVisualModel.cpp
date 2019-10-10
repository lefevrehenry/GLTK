#include "TexturedVisualModel.h"

#include <helper/FileRepository.h>
#include <helper/Message.h>
#include <opengl/Texture2D.h>

using namespace gl;
using namespace gl::helper;

TexturedVisualModel::TexturedVisualModel(const std::string& filename, const std::string& textureFilename) : VisualModel(filename),
    m_texture(new Texture2D())
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
