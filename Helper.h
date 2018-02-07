#ifndef HELPER_H
#define HELPER_H

#include "GLFWApplication.h"
#include "Camera.h"
#include "Message.h"
#include "Program.h"
#include "Shader.h"
#include "ShaderProgram.h"

// Standard Library
#include <fstream>
#include <string>


namespace gl {

namespace helper {

static bool getStringFromFile(const std::string& filename, std::string& dest) {
    std::ifstream filestream(filename, std::ios::in);

    if(!filestream.is_open()) {
        msg_error("Error") << "File not found: " << filename;
        return false;
    }

    dest = "";
    std::string line;

    while(getline(filestream, line)) {
        dest += line + "\n";
    }

    filestream.close();

    return true;
}

static ShaderProgram* CreateShaderProgram(ShaderProgram::ShaderProgramType shaderProgramType)
{
    typedef Shader::ShaderType ShaderType;
    typedef ShaderProgram::ShaderProgramType ShaderProgramType;

    ShaderProgram* shaderProgram = new ShaderProgram();

    std::string vs = "";
    std::string gs = "";
    std::string fs = "";

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    switch (shaderProgramType)
    {
    case ShaderProgramType::DrawBasic:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.vs", vs);
        vertexShader.compileSourceCode(vs);
        shaderProgram->addShader(vertexShader);

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.fs", fs);
        fragmentShader.compileSourceCode(fs);
        shaderProgram->addShader(fragmentShader);

        break;
    case ShaderProgramType::DrawNormal:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.vs", vs);
        vertexShader.compileSourceCode(vs);
        shaderProgram->addShader(vertexShader);

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.gs", gs);
        geometryShader.compileSourceCode(gs);
        shaderProgram->addShader(geometryShader);

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.fs", fs);
        fragmentShader.compileSourceCode(fs);
        shaderProgram->addShader(fragmentShader);

        break;
    }

    shaderProgram->link();

    GLFWApplication* app = GLFWApplication::getInstance();
    Camera* camera = app->getCamera();

    switch (shaderProgramType)
    {
    case ShaderProgramType::DrawBasic:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<glm::vec3>("color", glm::vec3(1,1,0));

        break;
    case ShaderProgramType::DrawNormal:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);

        break;
    }

    return shaderProgram;
}

}   // namespace helper

}   // namespace gl

#endif
