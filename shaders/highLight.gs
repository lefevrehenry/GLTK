#version 330 core

// type of input primitives
layout(triangles) in;

// type of output primitives
layout(line_strip, max_vertices = 4) out;

void main()
{
    vec4 p1 = gl_in[0].gl_Position;
    vec4 p2 = gl_in[1].gl_Position;
    vec4 p3 = gl_in[2].gl_Position;

    gl_Position = p1;
    EmitVertex();
    gl_Position = p2;
    EmitVertex();
    gl_Position = p3;
    EmitVertex();
    gl_Position = p1;
    EmitVertex();
    EndPrimitive();
}
