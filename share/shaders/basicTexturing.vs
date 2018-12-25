#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
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
out vec2 o_uvcoord;

void main()
{
    o_uvcoord = uvcoord;

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
