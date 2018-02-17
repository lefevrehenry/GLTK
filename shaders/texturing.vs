#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 uvcoord;

// uniform input
uniform mat4 mvp;
uniform mat3 normal_mat;

// data to fragment shader
out vec3 o_normal;
out vec2 o_uvcoord;

void main()
{
    o_normal = normal_mat * normal;
    o_uvcoord = uvcoord;
    gl_Position = mvp * vec4(position, 1.0);
}
