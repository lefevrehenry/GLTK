#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec2 uvcoord;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;

// uniform input
uniform mat4 mvp;
uniform mat3 normal_mat;
uniform sampler2D normalMap;

// data to fragment shader
out vec3 o_tangent;
out vec3 o_bitangent;
out vec3 o_normal;
out vec2 o_uvcoord;

void main()
{
    o_tangent = normalize(tangent);
    o_bitangent = normalize(bitangent);
    o_normal  = normalize(normal);
    o_uvcoord = uvcoord;

    gl_Position = mvp * vec4(position, 1.0);
}
