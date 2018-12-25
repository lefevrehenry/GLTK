#version 330 core

flat in int id;

out vec4 outColor;

void main()
{
    vec3 color = vec3(0,0,0);
    color[id] = 1;

    outColor = vec4(color,1.0);
}
