#ifndef HELPER_H
#define HELPER_H

#include "Camera.h"
#include "Message.h"
#include "Program.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
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
    case ShaderProgramType::BasicTexturing:

        getStringFromQrcFile(":/shaders/basicTexturing.vs", vs);
        getStringFromQrcFile(":/shaders/basicTexturing.fs", fs);

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
    case ShaderProgramType::Deferred:

        getStringFromQrcFile(":/shaders/deferred.vs", vs);
        getStringFromQrcFile(":/shaders/deferred.fs", fs);

        break;
    case ShaderProgramType::ShadowMapping:

        getStringFromQrcFile(":/shaders/shadowMapping.vs", vs);
        getStringFromQrcFile(":/shaders/shadowMapping.fs", fs);

        break;
    case ShaderProgramType::NormalMapping:

        getStringFromQrcFile(":/shaders/normalMapping.vs", vs);
        getStringFromQrcFile(":/shaders/normalMapping.fs", fs);

        break;
    case ShaderProgramType::CubeMap:

        getStringFromQrcFile(":/shaders/cubeMap.vs", vs);
        getStringFromQrcFile(":/shaders/cubeMap.fs", fs);

        break;
    case ShaderProgramType::EnvironmentMapping:

        getStringFromQrcFile(":/shaders/environmentMapping.vs", vs);
        getStringFromQrcFile(":/shaders/environmentMapping.fs", fs);

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

    glm::vec3 dir_light(-1,-1,-1);

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Normal:

        shaderProgram->addData<float>("scale", 0.5f);
        shaderProgram->addData<glm::vec3>("normalColor", glm::vec3(1,1,1));
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

        shaderProgram->addData<glm::vec3>("dir_light", dir_light);
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->setNbInstance(3);

        break;
    case ShaderProgramType::HighLight:

        shaderProgram->addData<glm::vec3>("color", glm::vec3(1.0,0.8,0.0));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
//        shaderProgram->set(OpenGLState::CullFace, GL_TRUE);
//        shaderProgram->set(OpenGLState::DepthMask, GL_FALSE);

        break;
    case ShaderProgramType::BasicTexturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Texturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::TangentSpace:

        shaderProgram->setPrimitiveMode(PrimitiveMode::POINTS);
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

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::VaoQuad:

        break;
    case ShaderProgramType::Deferred:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::ShadowMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::NormalMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::CubeMap:

        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::EnvironmentMapping:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    }

    return shaderProgram;
}

}   // namespace helper

}   // namespace gl

#endif
