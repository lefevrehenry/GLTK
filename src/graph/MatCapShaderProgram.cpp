#include "MatCapShaderProgram.h"

#include <gltk.h>
#include <ShaderProgramPrivate.h>
#include <VisualManager.h>

using namespace gl;

MatCapShaderProgram::MatCapShaderProgram() :
    m_matcapTexture()
{
    std::string vertexCode = GLTK::GetStringFromFile("shaders/matcap.vs");
    std::string fragmentCode = GLTK::GetStringFromFile("shaders/matcap.fs");

    setVertexShaderCode(vertexCode);
    setFragmentShaderCode(fragmentCode);

    ShaderProgram::link();

    this->attachUniformBufferTransform("transform");
    this->attachUniformBufferCamera("camera");
}

void MatCapShaderProgram::setMatCapTexture(const std::string& filename)
{
    std::string abspath;
    this->m_matcapTexture->load(filename);
    this->setUniformValue("matcap", this->m_matcapTexture);
}
