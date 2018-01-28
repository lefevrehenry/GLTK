#version 330 core

// type of input primitives
layout(points) in;

// type of output primitives
//layout(points, max_vertices = 1) out;
layout(line_strip, max_vertices = 2) out;

// uniform input
uniform mat4 mvp;

// data from vertex shader
in vec4 o_pos[1];
in vec3 o_normal[1];

void main()
{
    vec4 p1 = gl_in[0].gl_Position;
    vec4 p2 = o_pos[0];//vec4(gl_in[0].gl_Position.xyz + o_normal[0], 1.0);

    gl_Position = p1;
    EmitVertex();
    gl_Position = p2;
    EmitVertex();
    EndPrimitive();
}
