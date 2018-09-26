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
uniform vec3 dir_light;
uniform sampler2D colorMap;
uniform sampler2D normalMap;

// data from vertex shader
in vec3 o_tangent;
in vec3 o_bitangent;
in vec3 o_normal;
in vec2 o_uvcoord;

out vec4 outColor;

void main()
{
    vec2 uv = o_uvcoord;

    // normalized vectors needed for shading
    vec3 l = normalize(dir_light);

    vec3 t = normalize(o_tangent);
    vec3 b = normalize(o_bitangent);
    vec3 n = normalize(o_normal);
    mat3 tbn = mat3(t,b,n);
    n = tbn * (2 * texture(normalMap,uv).xyz - 1);

    // diffuse and specular components
    float diff = max(-dot(l,n),0.0);

    // final color
    outColor = texture(colorMap,uv);
    //outColor = diff * texture(colorMap,uv);
}
