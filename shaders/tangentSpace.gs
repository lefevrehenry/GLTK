#version 330 core

// type of input primitives
layout(points) in;

// type of output primitives
layout(line_strip, max_vertices = 6) out;

// data from vertex shader
in vec4 o_tpos[1];
in vec4 o_bpos[1];
in vec4 o_npos[1];

flat out int id;

void main()
{
    // tangent
    gl_Position = gl_in[0].gl_Position;
    id = 0;
    EmitVertex();
    gl_Position = o_tpos[0];
    id = 0;
    EmitVertex();
    EndPrimitive();

    // bitangent
    gl_Position = gl_in[0].gl_Position;
    id = 1;
    EmitVertex();
    gl_Position = o_bpos[0];
    id = 1;
    EmitVertex();
    EndPrimitive();

    // normal
    gl_Position = gl_in[0].gl_Position;
    id = 2;
    EmitVertex();
    gl_Position = o_npos[0];
    id = 2;
    EmitVertex();
    EndPrimitive();
}
