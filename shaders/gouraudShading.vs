#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
//layout(location = 2) in vec3 color;

// uniform input
uniform mat4 mvp;
uniform vec3 dir_light;
uniform vec3 color;

// data to fragment shader
out vec3 o_color;

void main()
{
    float d = -dot(normal, dir_light);
    d = clamp(d, 0.0, 1.0);

    o_color = d * color;
    gl_Position = mvp * vec4(position, 1.0);
}
