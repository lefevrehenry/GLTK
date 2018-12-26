#version 330 core

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

// input from vertex shader
in vec3 o_normal;
flat in int instanceID;

out vec4 outColor;

void main()
{
    vec4 color = vec4(0,0,0,1);
    color[instanceID] = 1;

    vec3 n = normalize(o_normal);
    float d = max(-dot(n, lightDirection), 0.0);

    outColor = d * color;
}
