#version 330 core

in vec3 o_normal;
flat in int instanceID;

uniform vec3 dir_light;

out vec4 outColor;

void main()
{
    vec3 color = vec3(0,0,0);
    color[instanceID] = 1;

    vec3 unit_normal = normalize(o_normal);
    float d = max(-dot(unit_normal, dir_light), 0.0);
    outColor = d * vec4(color, 1.0);
}
