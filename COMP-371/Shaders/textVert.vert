#version 450 core

//Get vertex location from layout
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

//Texture coord
out vec2 texCoord;

//Model View Projection matrix
uniform mat4 MVP;

void main()
{
	//Set the vertex position according to the MVP matrix
    gl_Position = MVP * vec4(pos, 1.0);
	textCoord = text;
}