#version 330 core

uniform vec3 dir_light;
uniform vec3 color;

in vec3 n;

out vec4 outColor;

void main()
{
    vec3 l = normalize(dir_light);
    float d = max(-dot(n, l), 0.0);
    outColor = d * vec4(color, 1.0);
}