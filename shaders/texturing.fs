#version 330 core

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// uniform input
uniform vec3 dir_light;
uniform sampler2D ambientMap;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specMap;

// data from vertex shader
in vec3 o_normal;
in vec3 o_tangent;
in vec3 o_bitangent;
in vec2 o_uvcoord;
in vec3 o_eyeView;

out vec4 outColor;

void main()
{
    vec2 uv = o_uvcoord;

    // normalized vectors needed for shading
    vec3 e = normalize(o_eyeView);
    vec3 l = normalize(NormalMatrix * dir_light);

    vec3 t = normalize(o_tangent);
    vec3 b = normalize(o_bitangent);
    vec3 n = normalize(o_normal);
    mat3 tbn = mat3(t,b,n);

    n = tbn * normalize(2 * texture(normalMap,uv).xyz - 1);
    n = NormalMatrix * n;

    // diffuse and specular components
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),shininess);

    // final color
    vec4 ambientColor = texture(ambientMap, uv);
    vec4 diffuseColor = texture(colorMap, uv);
    vec4 specularColor = texture(specMap, uv);

    outColor = ambientColor + (diff * diffuseColor) + (spec * specularColor);
    //outColor = ambientColor + (diff * diffuseColor);
}
