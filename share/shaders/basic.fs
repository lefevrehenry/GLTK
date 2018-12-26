#version 330 core

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

// data from geometry shader
in vec3 o_normal;

out vec4 outColor;

void main()
{
    vec3 unit_normal = normalize(o_normal);
    float d = max(-dot(unit_normal, lightDirection), 0.0);
    outColor = ambientColor + (d * diffuseColor);
}
