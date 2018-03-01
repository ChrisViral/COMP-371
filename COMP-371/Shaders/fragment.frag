#version 450 core

//Vertex colour
out vec4 fragColour;

//Input colour
uniform vec3 colour;
  
void main()
{
	//Set the vertex colour to the current input colour
    fragColour = vec4(colour, 1.0);
}