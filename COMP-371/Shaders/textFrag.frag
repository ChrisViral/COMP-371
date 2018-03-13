#version 450 core

//Vertex colour
out vec4 fragColour;

//Texture coordinate
in vec2 texCoord;

//Input texture
uniform sampler2D image;
  
void main()
{
	//Set the vertex colour to the current input colour
    fragColour = texture(image, texCoord);
}