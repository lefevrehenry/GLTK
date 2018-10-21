#version 330 core

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

// data from geometry shader
in vec3 o_normal;

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outDepth;

void main()
{
    float z = pow(gl_FragCoord.z, 8);

    outColor = (ambientColor + diffuseColor).xyz;
    outNormal = normalize(o_normal);
    outDepth = vec3(z, z, z);
}
