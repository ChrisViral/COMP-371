#version 450 core

layout (triangles) in;

layout (triangle_strip, max_vertices=18) out;

//Matrices
uniform mat4 shadows[6];

//Fragment position
out vec4 fragPosition;

void main()
{
    //Loop through faces
    for(int face = 0; face < 6; ++face)
    {
        //Render face
        gl_Layer = face;

        //Loop through vertices
        for(int i = 0; i < 3; ++i)
        {
            fragPosition = gl_in[i].gl_Position;
            gl_Position = shadows[face] * fragPosition;
            EmitVertex();
        }    
        EndPrimitive();
    }
} 