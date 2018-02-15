#version 330 core

// type of input primitives
layout(points) in;

// type of output primitives
layout(line_strip, max_vertices = 6) out;

uniform mat4 transform;
uniform mat4 orientation;
uniform vec3 scale;

out vec3 color;

void main()
{
    float sx = scale[0];
    float sy = scale[1];
    float sz = scale[2];

    vec4 p0 = transform * gl_in[0].gl_Position;
    vec4 p1 = p0 + transform * (orientation * vec4(sx,0,0,0));
    vec4 p2 = p0 + transform * (orientation * vec4(0,sy,0,0));
    vec4 p3 = p0 + transform * (orientation * vec4(0,0,sz,0));

    vec3 white = vec3(1,1,1);
    vec3 red   = vec3(1,0,0);
    vec3 blue  = vec3(0,1,0);
    vec3 green = vec3(0,0,1);

    // ox
    gl_Position = p0;
    color = white;
    EmitVertex();
    gl_Position = p1;
    color = red;
    EmitVertex();
    EndPrimitive();

    // oy
    gl_Position = p0;
    color = white;
    EmitVertex();
    gl_Position = p2;
    color = blue;
    EmitVertex();
    EndPrimitive();

    // oz
    gl_Position = p0;
    color = white;
    EmitVertex();
    gl_Position = p3;
    color = green;
    EmitVertex();
    EndPrimitive();
}
