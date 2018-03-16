#version 450 core

layout (location = 0) in vec3 pos;

//Matrices
uniform mat4 vpMat;
uniform mat4 model;

void main()
{
    //Simply output position
    gl_Position = vpMat * model * vec4(pos, 1.0);
}