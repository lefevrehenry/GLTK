#version 330 core

// type of input primitives
//layout(points) in;
layout(triangles) in;

// type of output primitives
layout(line_strip, max_vertices = 2) out;

// data from vertex shader
in vec4 o_pos[3];
//in vec3 o_normal[3];

void main()
{
    vec4 p1 = vec4(0,0,0,0);
    vec4 p2 = vec4(0,0,0,0);

    for (int i = 0; i < 3; ++i) {
        p1 += gl_in[i].gl_Position;
        p2 += o_pos[i];
        //p2 += vec4(gl_in[i].gl_Position.xyz + o_normal[i], 1.0);
    }

    p1 /= 3.0;
    p2 /= 3.0;
    p2 = normalize(p2);

    gl_Position = p1;
    EmitVertex();
    gl_Position = p2;
    EmitVertex();
    EndPrimitive();
}
