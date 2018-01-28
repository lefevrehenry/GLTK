#version 330 core

// type of input primitives
layout(triangles) in;

// type of output primitives
layout(triangle_strip, max_vertices = 9) out;

in vec3 o_normal[3];

out vec3 n;

void main()
{
    vec4 p1 = gl_in[0].gl_Position;
    vec3 n1 = o_normal[0];
    vec4 p2 = gl_in[1].gl_Position;
    vec3 n2 = o_normal[1];
    vec4 p3 = gl_in[2].gl_Position;
    vec3 n3 = o_normal[2];
    vec4 p4 = (p1 + p2 + p3) / 3.0;
    vec3 n4 = (n1 + n2 + n3) / 3.0;
    n4 = normalize(n4);

    // triangle 1
    gl_Position = p1;
    n = n1;
    EmitVertex();
    gl_Position = p2;
    n = n2;
    EmitVertex();
    gl_Position = p4;
    n = n4;
    EmitVertex();
    EndPrimitive();

    // triangle 2
    gl_Position = p2;
    n = n2;
    EmitVertex();
    gl_Position = p3;
    n = n3;
    EmitVertex();
    gl_Position = p4;
    n = n4;
    EmitVertex();
    EndPrimitive();

    // triangle 3
    gl_Position = p3;
    n = n3;
    EmitVertex();
    gl_Position = p1;
    n = n1;
    EmitVertex();
    gl_Position = p4;
    n = n4;
    EmitVertex();
    EndPrimitive();
}
