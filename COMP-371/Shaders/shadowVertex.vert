#version 450 core

layout (location = 0) in vec3 pos;

uniform mat4 vpMat;
uniform mat4 model;

void main()
{
    gl_Position = vpMat * model * vec4(pos, 1.0);
}