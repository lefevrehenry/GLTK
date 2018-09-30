#version 330 core

// data from vertex shader
in vec4 o_color;

out vec4 outColor;

void main()
{
    outColor = o_color;
}
