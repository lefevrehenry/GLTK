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
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// uniform input
uniform sampler2D colorMap;

// data to fragment shader
out vec3 o_tangent;
out vec3 o_bitangent;
out vec3 o_normal;
out vec2 o_uvcoord;

void main()
{
    o_tangent = tangent;
    o_bitangent = bitangent;
    o_normal  = normal;
    o_uvcoord = uvcoord;

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
