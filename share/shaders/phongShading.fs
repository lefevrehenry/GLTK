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

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

// input from vertex shader
in vec3 normalView;
in vec3 eyeView;

out vec4 outColor;

void main()
{
    // normal / view and light directions (in camera space)
    vec3 n = normalize(normalView);
    vec3 e = normalize(eyeView);
    vec3 l = normalize(NormalMatrix * lightDirection);

    // diffuse and specular components of the phong shading model
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),shininess);

    outColor = ambientColor + (diff * diffuseColor) + (spec * specularColor);
}
