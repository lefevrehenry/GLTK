#version 330 core

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

uniform sampler2D depthLight;

// input from vertex shader
in vec3 posLightCam;

out vec4 outColor;

void main()
{
    vec3 proj = (posLightCam + 1) / 2;
    vec4 color = texture(depthLight, proj.xy);
    float bias = 0.05f;
    float coef = 1.0;
    if (color.x < posLightCam.z - bias) {
        coef = 0.5;
    }
    outColor = coef * vec4(1,0,0,1);
}
