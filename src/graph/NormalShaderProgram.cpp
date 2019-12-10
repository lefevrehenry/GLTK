#include "NormalShaderProgram.h"

#include <gltk.h>

using namespace gl;

NormalShaderProgram::NormalShaderProgram() : ShaderProgram()
{
    std::string vertexCode = GLTK::GetStringFromFile("shaders/normal.vs");
    std::string geometryCode = GLTK::GetStringFromFile("shaders/normal.gs");
    std::string fragmentCode = GLTK::GetStringFromFile("shaders/normal.fs");

    setVertexShaderCode(vertexCode);
    setGeometryShaderCode(geometryCode);
    setFragmentShaderCode(fragmentCode);

    ShaderProgram::link();

    this->attachUniformBufferTransform("transform");
    this->attachUniformBufferCamera("camera");
}

void NormalShaderProgram::setNormalScale(float scale)
{
    bind();
    this->setUniformValue("scale", scale);
    unbind();
}

void NormalShaderProgram::setNormalColor(const glm::vec3& normalColor)
{
    bind();
    this->setUniformValue("normalColor", normalColor);
    unbind();
}
