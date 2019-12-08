#include "HighLightShaderProgram.h"

#include <gltk.h>

using namespace gl;

HighLightShaderProgram::HighLightShaderProgram() : ShaderProgram()
{
    std::string vertexCode = GLTK::GetStringFromFile("highLight.vs");
    std::string geometryCode = GLTK::GetStringFromFile("highLight.gs");
    std::string fragmentCode = GLTK::GetStringFromFile("highLight.fs");

    setVertexShaderCode(vertexCode);
    setGeometryShaderCode(geometryCode);
    setFragmentShaderCode(fragmentCode);

    ShaderProgram::link();

    this->attachUniformBufferTransform("transform");
    this->attachUniformBufferCamera("camera");

    this->setHighLightColor(glm::vec3(1,1,0));

//    shaderProgramPrivate->setRenderState<DepthFunc>(GL_LEQUAL);
//    shaderProgramPrivate->setRenderState<LineWidth>(2.0f);
//    shaderProgramPrivate->setRenderState<PolygonMode>(GL_LINE);
}

void HighLightShaderProgram::setHighLightColor(const glm::vec3& color)
{
    bind();
    this->setUniformValue("color", color);
    unbind();
}
