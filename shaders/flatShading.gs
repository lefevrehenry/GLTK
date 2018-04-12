#version 330 core

// type of input primitives
layout(triangles) in;

// type of output primitives
layout(triangle_strip, max_vertices = 3) out;

// data from vertex shader
in vec3 o_normalView[3];
in vec3 o_eyeView[3];

// data to fragment shader
out vec3 normalView;
out vec3 eyeView;

void main()
{
    vec3 n1 = o_normalView[0];
    vec3 n2 = o_normalView[1];
    vec3 n3 = o_normalView[2];

    vec3 _n = (n1 + n2 + n3) / 3.0;
    _n = normalize(_n);

    // generate triangle with uniform normal

    gl_Position = gl_in[0].gl_Position;
    normalView = _n;
    eyeView = o_eyeView[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    normalView = _n;
    eyeView = o_eyeView[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    normalView = _n;
    eyeView = o_eyeView[2];
    EmitVertex();
    EndPrimitive();
}
