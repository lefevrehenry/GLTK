#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;

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

uniform mat4 LightCam;

// data to fragment shader
out vec4 posLightCam;

void main()
{
    posLightCam = LightCam * ModelMatrix * vec4(position, 1.0);

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
