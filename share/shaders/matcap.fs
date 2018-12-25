#version 330 core

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
