#version 330 core

// data from vertex shader
in vec2 texCoord;

uniform sampler2D textureColor;
//uniform sampler2D textureNormal;
//uniform sampler2D textureDepth;

out vec4 color;

void main()
{
    vec3 bufferColor = texture2D(textureColor, texCoord).xyz;
    //vec3 bufferColor = texture2D(textureNormal, texCoord).xyz;
    //float bufferColor = texture2D(textureDepth, texCoord).x;

    //color = vec4(bufferColor.x, bufferColor.x, bufferColor.x, 1.0);
    color = vec4(bufferColor, 1.0);
}
