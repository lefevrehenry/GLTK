#ifndef GLTK_H
#define GLTK_H

namespace gl {

class GLTK
{

public:
    enum ShaderProgramType {
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
