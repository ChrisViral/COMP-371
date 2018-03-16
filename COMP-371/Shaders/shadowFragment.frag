#version 450 core

//Fragment position from geometry shader
in vec4 fragPosition;

//Needed values
uniform vec3 lightPosition;
uniform float farPlane;

void main()
{
    //Get correct depth
    gl_FragDepth = length(fragPosition.xyz - lightPosition) / farPlane;
}