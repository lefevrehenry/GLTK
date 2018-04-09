#version 330 core

layout(std140) uniform transform
{
    mat4 model;
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

// input from vertex shader
in vec3 normalView;
in vec3 eyeView;

// uniform input
uniform vec3 dir_light;
uniform mat3 normal_mat;

out vec4 outColor;

void main()
{
    // normal / view and light directions (in camera space)
    vec3 n = normalize(normalView);
    vec3 e = normalize(eyeView);
    vec3 l = normalize(normal_mat * dir_light);

    // diffuse and specular components of the phong shading model
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),shininess);

    outColor = ambientColor + (diff * diffuseColor) + (spec * specularColor);
}
