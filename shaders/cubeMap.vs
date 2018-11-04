#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// data to fragment shader
out vec3 texCoord;

void main()
{
    texCoord = position;
    vec4 pos = Projection * mat4(mat3(View)) * vec4(position, 1.0);
    gl_Position = pos.xyww;
}
