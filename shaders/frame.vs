#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform transform
{
    mat4 ModelMatrix;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// data to fragment shader
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

    gl_Position = ProjViewMatrix * ModelMatrix * orientation * vec4(15 * position, 1.0);
}
