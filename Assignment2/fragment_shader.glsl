#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;

void main() {

    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    float diffuseStrength = 1.0;
    float shininess = 32.0;
    float lightStrength = 1.0;
    float ambientLightStrength = 1.0;

    float ambient = 1;
    float diffuse = 1;
    float specular = 1;


    // TODO: Implement Blinn-Phong/Phong lighting model
    // Some useful functions:
    // - normalize(vec3 v): returns a normalized vector
    // - dot(vec3 a, vec3 b): returns the dot product of two vectors
    // - pow(float x, float y): returns x raised to the power of y
    // - max(float x, float y): returns the maximum value between x and y
    // - reflect(vec3 v, vec3 n): returns the reflection direction of the incident vector v and the normal n

    vec3 incident = normalize(lightPos - FragPos);
    vec3 view = normalize(viewPos - FragPos);
    vec3 normal = normalize(Normal);
    vec3 reflectDir = normalize(reflect(-incident, normal));

    float lambertian = max(dot(normal, incident), 0.0);

    ambient = ambientLightStrength * ambientStrength;

    diffuse = lambertian;
    // Quantize for toon shading
    diffuse = step(0.2, diffuse) * 0.6 + 0.2;
    diffuse *= lightStrength * diffuseStrength;

    specular = pow(max(dot(reflectDir, view), 0.0), shininess);
    // Quantize for toon shading
    specular = step(0.6, specular);
    specular *= lightStrength * specularStrength;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}