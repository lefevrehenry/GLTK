#version 330 core

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

// uniform input
uniform sampler2D colorMap;

// data from vertex shader
in vec3 o_normal;
in vec2 o_uvcoord;

out vec4 outColor;

void main()
{
    vec3 n = normalize(o_normal);
    vec3 l = normalize(lightDirection);

    float a = -.8f;
    float b = 1.0f;

    float diff = max(-dot(n,l),a);
    diff = (diff - a) / (b - a);

    outColor = diff * texture(colorMap, o_uvcoord);
}
