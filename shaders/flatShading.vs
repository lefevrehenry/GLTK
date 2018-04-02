#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

// uniform input
uniform mat4 mvp;

// data to geometry shader
out vec3 o_normal;

void main()
{
    o_normal = normal;
    gl_Position = mvp * vec4(position, 1.0);
}
