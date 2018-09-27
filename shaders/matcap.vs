#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

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

// data to fragment shader
out vec2 uv;

void main()
{
    vec4 p = vec4(position, 1.0);

    vec3 n = normalize( NormalMatrix * normal );
    vec3 e = normalize( vec3(view * ModelMatrix * p) );

    vec3 r = reflect(e, n);
    float m = 2. * sqrt( pow(r.x, 2.0) + pow(r.y, 2.0) + pow(r.z + 1.0, 2.0) );
    uv = r.xy / m + 0.5;

    gl_Position = ProjViewMatrix * ModelMatrix * p;
}
