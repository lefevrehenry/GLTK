#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;

// uniform input
uniform mat4 mvp;
uniform float scale;

// data to geometry shader
out vec4 o_tpos;
out vec4 o_bpos;
out vec4 o_npos;

void main()
{
    o_tpos = mvp * vec4(position + (scale * tangent), 1.0);
    o_bpos = mvp * vec4(position + (scale * bitangent), 1.0);
    o_npos = mvp * vec4(position + (scale * normal), 1.0);

    gl_Position = mvp * vec4(position, 1.0);
}
