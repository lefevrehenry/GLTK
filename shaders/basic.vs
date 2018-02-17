#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 mvp;

out vec3 o_normal;

void main()
{
    o_normal = normal;
    gl_Position = mvp * vec4(position, 1.0);
}
