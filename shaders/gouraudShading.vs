#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform transform
{
    mat4 ModelMatrix;
};

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// uniform input
uniform vec3 dir_light;

// data to fragment shader
out vec4 o_color;

void main()
{
    float diff = clamp(-dot(normal,dir_light), 0.0, 1.0);

    o_color = ambientColor + (diff * diffuseColor);
    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
