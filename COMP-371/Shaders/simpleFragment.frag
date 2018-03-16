#version 450 core

//Input colour
in vec3 colour;

//Vertex colour
out vec4 fragColour;
  
void main()
{
    //Output fragment colour as passed colour
    fragColour = vec4(colour, 1.0);
}