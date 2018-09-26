#version 330 core

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

// data from geometry shader
in vec3 o_normal;

uniform vec3 dir_light;

out vec4 outColor;

void main()
{
    vec3 unit_normal = normalize(o_normal);
    float d = max(-dot(unit_normal, dir_light), 0.0);
    outColor = ambientColor + (d * diffuseColor);
}
