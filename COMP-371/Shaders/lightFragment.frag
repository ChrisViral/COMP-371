#version 450 core

//Vertex colour
out vec4 fragColour;

//Texture coordinate
in vec2 texCoord;

//Lighting variables
const float ambient = 0.2;
const vec3 lightColour = vec3(1.0, 1.0, 1.0);

//Input texture
uniform int state;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 colour;
  
void main()
{
    vec3 pixColour;
    switch (state)
    {
        case 0:
            pixColour = colour; break;
        case 1:
            pixColour = texture(tex1, texCoord).xyz; break;
        case 2:
            pixColour = texture(tex2, texCoord).xyz; break;
    }

    vec3 ambientLight = lightColour * ambient;
    pixColour *= ambientLight;
    fragColour = vec4(pixColour, 1.0);

}