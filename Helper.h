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
    case ShaderProgramType::Basic:
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/basic.fs", fs);

        break;
    case ShaderProgramType::Normal:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.gs", gs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/normal.fs", fs);

        break;
    case ShaderProgramType::FlatShading:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/flatShading.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/flatShading.gs", gs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/flatShading.fs", fs);

        break;
    case ShaderProgramType::GouraudShading:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/gouraudShading.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/gouraudShading.fs", fs);

        break;
    case ShaderProgramType::PhongShading:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/phongShading.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/phongShading.fs", fs);

        break;

    case ShaderProgramType::Frame:

        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/frame.vs", vs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/frame.gs", gs);
        getStringFromFile("/home/henry/dev/QtProject/OpenGL/shaders/frame.fs", fs);

        break;
    }

    if (vs != "") {
        vertexShader.compileSourceCode(vs);
        shaderProgram->addShader(vertexShader);
    }

    if (gs != "") {
        geometryShader.compileSourceCode(gs);
        shaderProgram->addShader(geometryShader);
    }

    if (fs != "") {
        fragmentShader.compileSourceCode(fs);
        shaderProgram->addShader(fragmentShader);
    }

    shaderProgram->link();

    GLFWApplication* app = GLFWApplication::getInstance();
    Camera* camera = app->getCamera();

    glm::vec3 dir_light(-1,-1,-0.5);
    glm::vec3 color(1,0,0);

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addData<glm::vec3>("color", color);
        //shaderProgram->setDrawPrimitive(Mesh::TRIANGLES);

        break;
    case ShaderProgramType::Normal:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        //shaderProgram->setDrawPrimitive(Mesh::TRIANGLES);

        break;
    case ShaderProgramType::FlatShading:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<Camera, glm::mat3>("normal_mat", camera, &Camera::normal);
        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addData<glm::vec3>("color", color);
        //shaderProgram->setDrawPrimitive(Mesh::TRIANGLES);

        break;
    case ShaderProgramType::GouraudShading:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addData<glm::vec3>("color", color);

        break;
    case ShaderProgramType::PhongShading:

        shaderProgram->addData<Camera, glm::mat4>("view", camera, &Camera::view);
        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<Camera, glm::mat3>("normal_mat", camera, &Camera::normal);
        shaderProgram->addData<glm::vec3>("dir_light", dir_light);

        break;
    case ShaderProgramType::Frame:

        shaderProgram->addData<Camera, glm::mat4>("transform", camera, &Camera::mvp);
        shaderProgram->addData<glm::mat4>("orientation", glm::mat4());
        shaderProgram->addData<glm::vec3>("scale", glm::vec3(1,1,1));

        break;
    }

    return shaderProgram;
}

}   // namespace helper

}   // namespace gl

#endif
