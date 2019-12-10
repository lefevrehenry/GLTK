#ifndef GLTK_HIGHLIGHTSHADERPROGRAM_H
#define GLTK_HIGHLIGHTSHADERPROGRAM_H

#include <ShaderProgram.h>


namespace gl {

/**
 * @brief The HighLightShaderProgram class
 */
class HighLightShaderProgram : public ShaderProgram
{

public:
    HighLightShaderProgram();

public:
    void setHighLightColor(const glm::vec3& color);
};

}   // namespace gl

#endif
