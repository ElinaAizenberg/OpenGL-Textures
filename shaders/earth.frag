#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;
uniform float clouds_intensity;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
};

uniform Material material;
uniform Light light;


void main()
{
   // ambient light
   vec3 ambient = 0.2 * light.ambient;

   // diffuse light
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(-light.direction);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse *  diff * light.color;

   // The texture image represents all of the object's diffuse colors.
   // The ambient material's color equal to the diffuse material's color as well.
   vec3 result = (ambient + diffuse) * texture(material.diffuse, TexCoords).rgb;

   // Mix the resulting color with another texture (e.g., clouds texture) based on the clouds intensity.
   FragColor = mix(vec4(result, 1.0), texture(texture1, TexCoords), clouds_intensity);

};