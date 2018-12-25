#version 330 core

in vec3 o_normal;
flat in int instanceID;

uniform vec3 dir_light;

out vec4 outColor;

void main()
{
    vec4 color = vec4(0,0,0,1);
    color[instanceID] = 1;

    vec3 n = normalize(o_normal);
    float d = max(-dot(n, dir_light), 0.0);

    outColor = d * color;
}
