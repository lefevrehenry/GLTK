#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

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

void main()
{
    o_normal = ModelNormalMatrix * normal;
    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
