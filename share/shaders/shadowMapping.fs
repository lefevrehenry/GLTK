#version 330 core

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

uniform sampler2D depthLight;
uniform sampler2D colorTexture;

// input from vertex shader
in vec4 posLightCam;

out vec4 outColor;

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / 1280, gl_FragCoord.y /960);
    vec3 color = texture(colorTexture, uv).xyz;

    float bias = 0.005f;
    float coef = 1.0;

    float z = texture(depthLight, posLightCam.xy).x;
    if (z < posLightCam.z - bias)
        coef = 0.3;

    outColor = vec4(coef * color, 1);
}
