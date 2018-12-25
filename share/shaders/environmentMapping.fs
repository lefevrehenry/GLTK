#version 330 core

// uniform input
uniform samplerCube cubeMap;

// input from vertex shader
in vec3 normalWorld;
in vec3 eyeWorld;

out vec4 outColor;

void main()
{
    vec3 n = normalize(normalWorld);
    vec3 e = normalize(eyeWorld);

    vec3 r = reflect(e,n);
    float ratio = 1.0 / 1.309;
    //vec3 r = refract(e,n,ratio);

    outColor = texture(cubeMap,r);
}
