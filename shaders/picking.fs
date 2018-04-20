#version 330 core

// uniform input
uniform uint id;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 0, 0, 1.0);
}
