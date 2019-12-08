#include "PhongShaderProgram.h"

#include <gltk.h>

using namespace gl;

PhongShaderProgram::PhongShaderProgram() : ShaderProgram()
{
    std::string vertexCode = GLTK::GetStringFromFile("shaders/phongShading.vs");
    std::string fragmentCode = GLTK::GetStringFromFile("shaders/phongShading.fs");

    setVertexShaderCode(vertexCode);
    setFragmentShaderCode(fragmentCode);

    ShaderProgram::link();

    this->attachUniformBufferTransform("transform");
    this->attachUniformBufferMaterial("material");
    this->attachUniformBufferCamera("camera");
    this->attachUniformBufferLight("light");
}
