#ifndef GLTK_H
#define GLTK_H

// Standard Library
#include <map>
#include <string>


namespace gl {

class GLTK
{

public:
    static std::map<std::string, std::string> getMapFromIniFile(const std::string& filename);

public:
    enum class ShaderProgramType {
        Basic,
        Normal,
        FlatShading,
        GouraudShading,
        PhongShading,
        Frame,
        HighLight,
        BasicTexturing,
        Texturing,
        TangentSpace,
        Picking,
        OutLine,
        MatCap,
        VaoQuad,
        Deferred,
        ShadowMapping,
        NormalMapping,
        CubeMap,
        EnvironmentMapping
    };

};

}   // namespace gl

#endif
