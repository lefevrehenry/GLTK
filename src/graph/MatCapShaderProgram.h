#ifndef GLTK_MATCAPSHADERPROGRAM_H
#define GLTK_MATCAPSHADERPROGRAM_H

#include <ShaderProgram.h>
#include <Texture2D.h>


namespace gl {

/**
 * @brief The MatCapShaderProgram class
 */
class MatCapShaderProgram : public ShaderProgram
{
public:
    using SPtr = std::shared_ptr<MatCapShaderProgram>;

public:
    MatCapShaderProgram();

public:
    void setMatCapTexture(const std::string& filename);

private:
    Texture2D::SPtr m_matcapTexture;

};

}   // namespace gl

#endif
