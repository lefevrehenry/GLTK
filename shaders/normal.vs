#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

// uniform input
uniform mat4 mvp;
uniform mat3 normal_mat;

// data to geometry shader
out vec4 o_pos;
out vec3 o_normal;

void main()
{
    o_pos = mvp * vec4(position + normal, 1.0);
    o_normal = normalize(normal_mat * normal);
    gl_Position = mvp * vec4(position, 1.0);
}
