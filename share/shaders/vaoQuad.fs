#version 330 core

// data from vertex shader
in vec2 fragCoord;

uniform sampler2D textureColor;
//uniform sampler2D textureNormal;
//uniform sampler2D textureDepth;

out vec4 color;

void main()
{
    vec3 bufferColor = texture2D(textureColor, fragCoord).xyz;
    //vec3 bufferNormal = texture2D(textureNormal, fragCoord).xyz;
    //vec3 bufferDepth = vec3(texture2D(textureDepth, fragCoord).x);

    color = vec4(bufferColor, 1.0);
}
