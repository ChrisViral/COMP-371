#version 450 core

//Material
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//Light
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//Vertex colour
out vec4 fragColour;

//Input vectors
in vec3 normal;
in vec3 fragPosition;
in vec2 texCoord;

//Texture
uniform int state;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 colour;

//Lighting
uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;
  
void main()
{
    //Pixel colour
    vec3 fragmentColour;
    switch (state)
    {
        case 0:
            fragmentColour = colour; break;
        case 1:
            fragmentColour = vec3(texture(tex1, texCoord)); break;
        case 2:
            fragmentColour = vec3(texture(tex2, texCoord)); break;
        default:
            fragmentColour = vec3(1.0); break;
    }
    vec3 ambient = light.ambient * material.ambient;

    vec3 n = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPosition);
    vec3 diffuse = max(dot(n, lightDir), 0.0) * light.diffuse * material.diffuse;

    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, n);
    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * light.specular * material.specular;

    fragColour = vec4((ambient + diffuse + specular) * fragmentColour, 1.0);

}