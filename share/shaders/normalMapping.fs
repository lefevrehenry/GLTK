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

layout(std140) uniform light
{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
};

// uniform input
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D occlusionMap;

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
    vec3 l = normalize(NormalMatrix * lightDirection);
    //vec3 np = normalize(NormalMatrix * o_normal);

    vec3 t = normalize(o_tangent);
    vec3 b = normalize(o_bitangent);
    vec3 n = normalize(o_normal);
    mat3 tbn = mat3(t,b,n);

    n = normalize(tbn * (2 * texture(normalMap,uv).xyz - 1));
    n = NormalMatrix * n;

    // diffuse components
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),shininess);

    // final color
    vec4 diffuseColor = texture(colorMap, uv);
    vec4 specularColor = vec4(lightColor,1.0);

    vec4 ao = texture(occlusionMap,uv).xyzw;

    // final color
    outColor = (diff * diffuseColor) + (spec * specularColor);
}
