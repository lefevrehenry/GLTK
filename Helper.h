#ifndef HELPER_H
#define HELPER_H

#include "Camera.h"
#include "FileRepository.h"
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

//static bool getStringFromFile(const std::string& filename, std::string& dest)
//{
//    QFile file(QString::fromStdString(filename));
//    file.open(QIODevice::ReadOnly);

//    if (!file.isOpen()) {
//        msg_error("Helper") << "Could not open file " << filename;
//        return false;
//    }

//    dest = file.readAll().toStdString();

//    file.close();

//    return true;
//}

static ShaderProgram* CreateShaderProgram(ShaderProgram::ShaderProgramType shaderProgramType)
{
    typedef Shader::ShaderType ShaderType;
    typedef ShaderProgram::ShaderProgramType ShaderProgramType;

    ShaderProgram* shaderProgram = new ShaderProgram();

    std::string vertexFilename = "";
    std::string geometryFilename = "";
    std::string fragmentFilename = "";

    std::string vs = "";
    std::string gs = "";
    std::string fs = "";

    Shader vertexShader(ShaderType::Vertex);
    Shader geometryShader(ShaderType::Geometry);
    Shader fragmentShader(ShaderType::Fragment);

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        vertexFilename = "shaders/basic.vs";
        fragmentFilename = "shaders/basic.fs";

        break;
    case ShaderProgramType::Normal:

        vertexFilename = "shaders/normal.vs";
        geometryFilename = "shaders/normal.gs";
        fragmentFilename = "shaders/normal.fs";

        break;
    case ShaderProgramType::FlatShading:

        vertexFilename = "shaders/flatShading.vs";
        geometryFilename = "shaders/flatShading.gs";
        fragmentFilename = "shaders/flatShading.fs";

        break;
    case ShaderProgramType::GouraudShading:

        vertexFilename = "shaders/gouraudShading.vs";
        fragmentFilename = "shaders/gouraudShading.fs";

        break;
    case ShaderProgramType::PhongShading:

        vertexFilename = "shaders/phongShading.vs";
        fragmentFilename = "shaders/phongShading.fs";

        break;

    case ShaderProgramType::Frame:

        vertexFilename = "shaders/frame.vs";
        fragmentFilename = "shaders/frame.fs";

        break;
    case ShaderProgramType::HighLight:

        vertexFilename = "shaders/highLight.vs";
        geometryFilename = "shaders/highLight.gs";
        fragmentFilename = "shaders/highLight.fs";

        break;
    case ShaderProgramType::BasicTexturing:

        vertexFilename = "shaders/basicTexturing.vs";
        fragmentFilename = "shaders/basicTexturing.fs";

        break;
    case ShaderProgramType::Texturing:

        vertexFilename = "shaders/texturing.vs";
        fragmentFilename = "shaders/texturing.fs";

        break;
    case ShaderProgramType::TangentSpace:

        vertexFilename = "shaders/tangentSpace.vs";
        geometryFilename = "shaders/tangentSpace.gs";
        fragmentFilename = "shaders/tangentSpace.fs";

        break;
    case ShaderProgramType::Picking:

        vertexFilename = "shaders/picking.vs";
        fragmentFilename = "shaders/picking.fs";

        break;
    case ShaderProgramType::OutLine:

        vertexFilename = "shaders/outline.vs";
        fragmentFilename = "shaders/outline.fs";

        break;
    case ShaderProgramType::MatCap:

        vertexFilename = "shaders/matcap.vs";
        fragmentFilename = "shaders/matcap.fs";

        break;
    case ShaderProgramType::VaoQuad:

        vertexFilename = "shaders/vaoQuad.vs";
        fragmentFilename = "shaders/vaoQuad.fs";

        break;
    case ShaderProgramType::Deferred:

        vertexFilename = "shaders/deferred.vs";
        fragmentFilename = "shaders/deferred.fs";

        break;
    case ShaderProgramType::ShadowMapping:

        vertexFilename = "shaders/shadowMapping.vs";
        fragmentFilename = "shaders/shadowMapping.fs";

        break;
    case ShaderProgramType::NormalMapping:

        vertexFilename = "shaders/normalMapping.vs";
        fragmentFilename = "shaders/normalMapping.fs";

        break;
    case ShaderProgramType::CubeMap:

        vertexFilename = "shaders/cubeMap.vs";
        fragmentFilename = "shaders/cubeMap.fs";

        break;
    case ShaderProgramType::EnvironmentMapping:

        vertexFilename = "shaders/environmentMapping.vs";
        fragmentFilename = "shaders/environmentMapping.fs";

        break;
    }

    if (DataRepository.findFile(vertexFilename))
        getStringFromFile(vertexFilename, vs);

    if (DataRepository.findFile(geometryFilename))
        getStringFromFile(geometryFilename, gs);

    if (DataRepository.findFile(fragmentFilename))
        getStringFromFile(fragmentFilename, fs);

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

    switch (shaderProgramType)
    {
    case ShaderProgramType::Basic:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Normal:

        shaderProgram->addData<float>("scale", 0.5f);
        shaderProgram->addData<glm::vec3>("normalColor", glm::vec3(1,1,1));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::FlatShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::GouraudShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::PhongShading:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

        break;
    case ShaderProgramType::Frame:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);
        shaderProgram->setNbInstance(3);

        break;
    case ShaderProgramType::HighLight:

        shaderProgram->addData<glm::vec3>("color", glm::vec3(1.0,0.8,0.0));
        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->set<CullFace>(GL_TRUE);
        shaderProgram->set<DepthMask>(GL_FALSE);
        shaderProgram->set<DepthFunc>(GL_LESS);

        break;
    case ShaderProgramType::BasicTexturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);

        break;
    case ShaderProgramType::Texturing:

        shaderProgram->addUniformBlock("transform", VisualManager::TransformIndex);
        shaderProgram->addUniformBlock("material", VisualManager::MaterialIndex);
        shaderProgram->addUniformBlock("camera", VisualManager::CameraIndex);
        shaderProgram->addUniformBlock("light", VisualManager::LightIndex);

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
        shaderProgram->set<CullFace>(GL_FALSE);
        shaderProgram->set<DepthFunc>(GL_LEQUAL);

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
