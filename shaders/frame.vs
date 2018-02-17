#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 mvp;
uniform mat3 normal_mat;
uniform mat4 model;
uniform vec3 scale;

out vec3 o_normal;
flat out int instanceID;

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float sin = sin(angle);
    float cos = cos(angle);
    float mc = 1.0 - cos;

    return mat4(mc * axis.x * axis.x + cos, mc * axis.x * axis.y - axis.z * sin, mc * axis.z * axis.x + axis.y * sin, 0.0,
                mc * axis.x * axis.y + axis.z * sin, mc * axis.y * axis.y + cos, mc * axis.y * axis.z - axis.x * sin, 0.0,
                mc * axis.z * axis.x - axis.y * sin, mc * axis.y * axis.z + axis.x * sin, mc * axis.z * axis.z + cos, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

void main()
{
    mat4 orientation;

    if (gl_InstanceID == 0)
        orientation = mat4(1.0);

    if (gl_InstanceID == 1)
        orientation = rotationMatrix(vec3(0,0,1), radians(-90));

    if (gl_InstanceID == 2)
        orientation = rotationMatrix(vec3(0,1,0), radians(90));

    o_normal = mat3(orientation) * normal;
    instanceID = gl_InstanceID;
    gl_Position = mvp * orientation * vec4(scale * position, 1.0);
}
