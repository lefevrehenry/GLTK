#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec3 bitangent;
layout(location = 4) in vec2 uvcoord;

layout(std140) uniform transform
{
    mat4 ModelMatrix;
    mat3 ModelNormalMatrix;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// data to fragment shader
out vec3 o_normal;
out vec3 o_tangent;
out vec3 o_bitangent;
out vec2 o_uvcoord;
out vec3 o_eyeView;

void main()
{
    o_normal = ModelNormalMatrix * normal;
    o_tangent = mat3(ModelMatrix) * tangent;
    o_bitangent = mat3(ModelMatrix) * bitangent;
    o_uvcoord = uvcoord;

    o_eyeView = (View * ModelMatrix * vec4(position,1.0)).xyz;

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
