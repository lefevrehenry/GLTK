#version 330 core

// uniform input
uniform vec4 index;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = index;
}
