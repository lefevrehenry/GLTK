#version 330 core

layout(std140) uniform transform
{
    mat4 ModelMatrix;
};

layout(std140) uniform camera
{
    mat4 view;
    mat4 projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// uniform input
uniform sampler2D matcap;

// input from vertex shader
in vec2 uv;

out vec4 outColor;

void main()
{
    vec3 color = texture2D(matcap, uv).rgb;
    outColor = vec4(color,1.0);
}
