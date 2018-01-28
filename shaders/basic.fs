#version 330 core

uniform vec3 color;

in vec3 n;

out vec4 outColor;

void main()
{
    vec3 light = vec3(-1, -1, -0.5);
    vec3 norm = normalize(n);
    float d = -dot(n, light);
    d = clamp(d, 0.0, 1.0);
    outColor = d * vec4(color, 1.0);
}
