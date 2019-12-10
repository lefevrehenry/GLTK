#ifndef GLTK_NORMALSHADERPROGRAM_H
#define GLTK_NORMALSHADERPROGRAM_H

#include <ShaderProgram.h>


namespace gl {

/**
 * @brief The NormalShaderProgram class
 */
class NormalShaderProgram : public ShaderProgram
{

public:
    NormalShaderProgram();

public:
    void setNormalScale(float scale);
    void setNormalColor(const glm::vec3& normalColor);

};

}   // namespace gl

#endif
