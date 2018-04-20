#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;

// uniform input
uniform mat4 transform;
uniform mat4 camera;

void main()
{
    gl_Position = camera * transform * vec4(position, 1.0);
}
