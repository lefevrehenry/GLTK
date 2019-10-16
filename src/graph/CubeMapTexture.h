#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

#include <graph/Texture.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The CubeMapTexture class
 */
class CubeMapTexture : public Texture
{

public:
    using SPtr = std::shared_ptr<CubeMapTexture>;

public:
    CubeMapTexture();
    CubeMapTexture(const std::string& filename);

};

}   // namespace gl

#endif
