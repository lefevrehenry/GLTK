#version 330 core

// input from vertex shader
in vec3 normalView;
in vec3 eyeView;

// uniform input
uniform vec3 dir_light;
uniform mat3 normal_mat;

out vec4 outColor;

void main()
{
    const vec3 ambientColor  = vec3(0.3,0.3,0.2);
    const vec3 diffuseColor  = vec3(0.3,0.5,0.8);
    const vec3 specularColor = vec3(0.8,0.8,0.8);
    //const vec3 ambientColor  = vec3(0.3,0.3,0.2);
    //const vec3 diffuseColor  = vec3(1.0,0.0,0.0);
    //const vec3 specularColor = vec3(0.8,0.8,0.8);
    const float et = 50.0;

    // normal / view and light directions (in camera space)
    vec3 n = normalize(normalView);
    vec3 e = normalize(eyeView);
    vec3 l = normalize(normal_mat * dir_light);

    // diffuse and specular components of the phong shading model
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),et);

    vec3 color = ambientColor + (diff * diffuseColor) + (spec * specularColor);
    outColor = vec4(color, 1.0);
}
