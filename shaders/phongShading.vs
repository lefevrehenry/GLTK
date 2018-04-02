#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform transform
{
    mat4 model;
};

// uniform input
uniform mat4 view;
uniform mat4 mvp;
uniform mat3 normal_mat;

// data to fragment shader
out vec3 normalView;
out vec3 eyeView;

void main()
{
    normalView = normal_mat * normal;
    eyeView = (view * vec4(position,1.0)).xyz;

    gl_Position = mvp * model * vec4(position, 1.0);
}
