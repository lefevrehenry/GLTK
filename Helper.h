#ifndef HELPER_H
#define HELPER_H

#include "Camera.h"
#include "GLFWApplication.h"
#include "Message.h"
#include "Program.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Viewer.h"
#include "VisualManager.h"

// Standard Library
#include <fstream>
#include <map>
#include <string>

// Qt
#include <QFile>
#include <QString>

namespace gl {

namespace helper {

static std::map<std::string, std::string> getMapFromIniFile(const std::string& filename)
{
    std::map<std::string, std::string> map;

    std::ifstream iniFile(filename.c_str());
    if (!iniFile.is_open()) {
        msg_error("Helper") << "Cannot read ini file " << filename;
    }

    std::string line;
    while (std::getline(iniFile, line)) {
        size_t equalPos = line.find_first_of('=');
        if (equalPos != std::string::npos) {
            const std::string key = line.substr(0, equalPos);
            const std::string value = line.substr(equalPos + 1, std::string::npos);
            map[key] = value;
        }
    }

    return map;
}

static bool getStringFromFile(const std::string& filename, std::string& dest)
{
    std::ifstream filestream(filename, std::ios::in);

    if(!filestream.is_open()) {
        msg_error("Helper") << "File " << filename << " not found";
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

static bool getStringFromQrcFile(const std::string& filename, std::string& dest)
{
    QFile file(QString::fromStdString(filename));
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen()) {
        msg_error("Helper") << "Could not open file " << filename;
        return false;
    }

    dest = file.readAll().toStdString();

    file.close();

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

        getStringFromQrcFile(":/shaders/basic.vs", vs);
        getStringFromQrcFile(":/shaders/basic.fs", fs);

        break;
    case ShaderProgramType::Normal:

        getStringFromQrcFile(":/shaders/normal.vs", vs);
        getStringFromQrcFile(":/shaders/normal.gs", gs);
        getStringFromQrcFile(":/shaders/normal.fs", fs);

        break;
    case ShaderProgramType::FlatShading:

        getStringFromQrcFile(":/shaders/flatShading.vs", vs);
        getStringFromQrcFile(":/shaders/flatShading.gs", gs);
        getStringFromQrcFile(":/shaders/flatShading.fs", fs);

        break;
    case ShaderProgramType::GouraudShading:

        getStringFromQrcFile(":/shaders/gouraudShading.vs", vs);
        getStringFromQrcFile(":/shaders/gouraudShading.fs", fs);

        break;
    case ShaderProgramType::PhongShading:

        getStringFromQrcFile(":/shaders/phongShading.vs", vs);
        getStringFromQrcFile(":/shaders/phongShading.fs", fs);

        break;

    case ShaderProgramType::Frame:

        getStringFromQrcFile(":/shaders/frame.vs", vs);
        getStringFromQrcFile(":/shaders/frame.fs", fs);

        break;
    case ShaderProgramType::HighLight:

        getStringFromQrcFile(":/shaders/highLight.vs", vs);
        getStringFromQrcFile(":/shaders/highLight.gs", gs);
        getStringFromQrcFile(":/shaders/highLight.fs", fs);

        break;
    case ShaderProgramType::Texturing:

        getStringFromQrcFile(":/shaders/texturing.vs", vs);
        getStringFromQrcFile(":/shaders/texturing.fs", fs);

        break;
    case ShaderProgramType::TangentSpace:

        getStringFromQrcFile(":/shaders/tangentSpace.vs", vs);
        getStringFromQrcFile(":/shaders/tangentSpace.gs", gs);
        getStringFromQrcFile(":/shaders/tangentSpace.fs", fs);

        break;
    case ShaderProgramType::Picking:

        getStringFromQrcFile(":/shaders/picking.vs", vs);
        getStringFromQrcFile(":/shaders/picking.fs", fs);

        break;
    case ShaderProgramType::OutLine:

        getStringFromQrcFile(":/shaders/outline.vs", vs);
        getStringFromQrcFile(":/shaders/outline.fs", fs);

        break;
    case ShaderProgramType::MatCap:

        getStringFromQrcFile(":/shaders/matcap.vs", vs);
        getStringFromQrcFile(":/shaders/matcap.fs", fs);

        break;
    case ShaderProgramType::VaoQuad:

        getStringFromQrcFile(":/shaders/vaoQuad.vs", vs);
        getStringFromQrcFile(":/shaders/vaoQuad.fs", fs);

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

    float normalScale = 0.5;

    glm::vec3 dir_light(-1,-1,-1);
    glm::vec3 color(1,0,0);
    static Texture colorMap;
    if (!colorMap.isLoaded())
        colorMap.load("textures/chesterfield-color.png");
    static Texture normalMap;
    if (!normalMap.isLoaded())
        normalMap.load("textures/chesterfield-normal.png");
    static Texture matcapTexture;
    if (!matcapTexture.isLoaded())
        matcapTexture.load("textures/hot.jpg");

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Normal:

        shaderProgram->addData<float>("scale", normalScale);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::FlatShading:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::GouraudShading:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::PhongShading:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Frame:

        shaderProgram->addData<Camera, glm::mat4>("mvp", camera, &Camera::mvp);
        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addData<glm::vec3>("scale", glm::vec3(1,1,1));
        //shaderProgram->setNbInstance(3);

        break;
    case ShaderProgramType::HighLight:

//        shaderProgram->setPrimitiveMode(PrimitiveMode::TRIANGLES);
        shaderProgram->addData<glm::vec3>("color", glm::vec3(1.0,0.8,0.0));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Texturing:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addData<Texture>("colorMap", colorMap);
        shaderProgram->addData<Texture>("normalMap", normalMap);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::TangentSpace:

        shaderProgram->setPrimitiveMode(PrimitiveMode::POINTS);
        shaderProgram->addData<float>("scale", normalScale);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Picking:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::OutLine:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::MatCap:

        shaderProgram->addData<Texture>("matcap", matcapTexture);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::VaoQuad:

        break;
    }

    return shaderProgram;
}

}   // namespace helper

}   // namespace gl

#endif
