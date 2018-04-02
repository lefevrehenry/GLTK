#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

// uniform input
uniform mat4 mvp;
uniform float scale;

// data to geometry shader
out vec4 o_pos;

void main()
{
    o_pos = mvp * vec4(position + (scale * normal), 1.0);
    //o_normal = normalize(normal_mat * normal);
    gl_Position = mvp * vec4(position, 1.0);
}
