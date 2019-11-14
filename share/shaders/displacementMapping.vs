#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec3 bitangent;
layout(location = 4) in vec2 uvcoord;

layout(std140) uniform transform
{
    mat4 ModelMatrix;
    mat3 ModelNormalMatrix;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

uniform sampler2D normalMap;
uniform sampler2D heightMap;

// data to fragment shader
out vec3 o_normal;

void main()
{
    // world space
    vec3 t = tangent; //normalize(mat3(ModelMatrix) * tangent);
    vec3 b = bitangent; //normalize(mat3(ModelMatrix) * bitangent);
    vec3 n = normal; //normalize(ModelNormalMatrix * normal);

    vec3 tbn_normal = (texture(normalMap, uvcoord).xyz);
    mat3 tbn = mat3(t,b,n);

    vec3 w_normal = normalize(tbn * tbn_normal);    // world space normal
    o_normal = normalize(ModelNormalMatrix * w_normal);  // eye space normal

    float depth = texture(heightMap, uvcoord).r;
    vec3 p = position + (0.1 * depth * normal);

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(p, 1.0);
}
