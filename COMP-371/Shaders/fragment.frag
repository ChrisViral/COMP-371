#version 450 core

//Vertex colour
out vec4 fragColour;

//Texture coordinate
in vec2 texCoord;

//Input texture
uniform int state;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 colour;
  
void main()
{
    switch (state)
    {
        case 0:
            fragColour = vec4(colour, 1.0); break;
        case 1:
            fragColour = texture(tex1, texCoord); break;
        case 2:
            fragColour = texture(tex2, texCoord); break;
    }
}