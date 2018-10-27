#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;

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

uniform mat4 LightCam;

// data to fragment shader
out vec3 posLightCam;

void main()
{
    vec4 proj = LightCam * ModelMatrix * vec4(position, 1.0);
    posLightCam = proj.xyz / proj.w;

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
