#version 330 core

uniform vec3 normalColor;

out vec4 outColor;

void main()
{
    outColor = vec4(normalColor,1.0);
}
