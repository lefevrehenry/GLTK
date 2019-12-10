#ifndef GLTK_GLTK_H
#define GLTK_GLTK_H

// Standard Library
#include <map>
#include <string>


namespace gl {

class GLTK
{

public:
    static std::map<std::string, std::string> GetMapFromIniFile(const std::string& filename);
    static std::string GetStringFromFile(const std::string& filename);

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
        EnvironmentMapping,
        DisplacementMapping
    };

    enum class OpenGLDepthFunc {
        Never,
        Less,
        Equal,
        Lequal,
        Greater,
        NotEqual,
        Gequal,
        Always
    };
};

}   // namespace gl

#endif
