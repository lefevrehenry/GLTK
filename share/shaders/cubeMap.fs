#version 330 core

// uniform input
uniform samplerCube cubeMap;

// data from vertex shader
in vec3 texCoord;

out vec4 outColor;

void main()
{
    outColor = texture(cubeMap, texCoord);
}
