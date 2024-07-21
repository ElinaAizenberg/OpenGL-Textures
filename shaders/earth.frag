#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

//uniform sampler2D texture1;
uniform sampler2D texture2;

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

       // ambient
           vec3 ambient = 0.2 * light.ambient;

           // diffuse
           vec3 norm = normalize(Normal);
           vec3 lightDir = normalize(-light.direction);
           float diff = max(dot(norm, lightDir), 0.0);
           vec3 diffuse = light.diffuse *  diff * light.color;

           vec3 result = (ambient + diffuse) * texture(material.diffuse, TexCoords).rgb;

 	FragColor = mix(vec4(result, 1.0), texture(texture2, TexCoords), clouds_intensity);



};