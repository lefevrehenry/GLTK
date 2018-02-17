#version 330 core

uniform vec3 dir_light;
uniform sampler2D textureMap;

in vec3 o_normal;
in vec2 o_uvcoord;

out vec4 outColor;

void main()
{
    vec4 textureColor = texture2D(textureMap, o_uvcoord);
    float d = max(-dot(normalize(o_normal), dir_light), 0.0);
    outColor = textureColor;
}
