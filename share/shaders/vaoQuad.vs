#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 4) in vec2 textureCoord;

// data to fragment shader
out vec2 fragCoord;

void main()
{
    fragCoord = textureCoord;
    gl_Position = vec4(position, 1.0);
}
