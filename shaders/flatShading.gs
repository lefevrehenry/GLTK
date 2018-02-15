#version 330 core

// type of input primitives
layout(triangles) in;

// type of output primitives
layout(triangle_strip, max_vertices = 3) out;

// data from vertex shader
in vec3 o_normal[3];

out vec3 n;

void main()
{
    vec3 n1 = o_normal[0];
    vec3 n2 = o_normal[1];
    vec3 n3 = o_normal[2];

    vec3 _n = (n1 + n2 + n3) / 3.0;
    _n = normalize(_n);

    // triangle with uniform normal
    gl_Position = gl_in[0].gl_Position;
    n = _n;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    n = _n;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    n = _n;
    EmitVertex();
    EndPrimitive();
}
