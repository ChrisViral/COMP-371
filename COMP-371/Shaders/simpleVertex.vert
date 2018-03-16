#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertexColour;

//Output colour
out vec3 colour;

//Model View Projection matrix
uniform mat4 vpMat;
uniform mat4 model;

void main()
{
	//Set the vertex position according to the MVP matrix
    gl_Position = vpMat * model * vec4(pos, 1.0);
    //Pass on vertex colour
    colour = vertexColour;
}