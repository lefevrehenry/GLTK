#version 330 core

// uniform input
//uniform vec3 dir_light;
uniform sampler2D colorMap;

// data from vertex shader
in vec2 o_uvcoord;

out vec4 outColor;

void main()
{
    outColor = texture(colorMap, o_uvcoord);
}
