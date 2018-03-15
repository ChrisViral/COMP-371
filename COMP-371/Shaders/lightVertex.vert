#version 450 core

//Get vertex location from layout
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

//Output vectors
out vec3 normal;
out vec3 fragPosition;
out vec2 texCoord;
out vec4 lightSpacePosition;

//Model View Projection matrix
uniform mat4 vpMat;
uniform mat4 model;
uniform mat4 lightSpace;

void main()
{
	//Set the vertex position according to the MVP matrix
    vec4 uniPos = vec4(pos, 1.0);
    vec4 p = model * uniPos;
    gl_Position = vpMat * p;
    normal = mat3(transpose(inverse(model))) * norm;
    fragPosition = vec3(p);
    lightSpacePosition = lightSpace * uniPos;
    texCoord = tex;
}