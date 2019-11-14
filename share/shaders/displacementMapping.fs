#version 330 core

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// uniform input
//uniform sampler2D colorMap;

// data from vertex shader
in vec3 o_normal;

out vec4 outColor;

void main()
{
    vec3 n = normalize(o_normal);         // normal eye space
    vec3 l = normalize(lightDirection);   // light eye space

    float diff = max(-dot(n,l),0.0);

    vec3 diffColor = diff * vec3(1,0,0);
    outColor = vec4(diffColor,1);
}
