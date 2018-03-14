#version 450 core

//Vertex colour
out vec4 fragColour;

//Input vectors
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

//Uniforms
uniform int state;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 colour;
uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform float ambientStrength;
  
void main()
{
    vec3 pixColour;
    switch (state)
    {
        case 0:
            pixColour = colour; break;
        case 1:
            pixColour = vec3(texture(tex1, texCoord)); break;
        case 2:
            pixColour = vec3(texture(tex2, texCoord)); break;
    }
    vec3 ambient = lightColour * ambientStrength;
    vec3 diffuse = max(dot(normalize(normal), normalize(lightPosition - fragPos)), 0.0) * lightColour;
    fragColour = vec4((ambient + diffuse) * pixColour, 1.0);

}