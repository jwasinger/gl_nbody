#version 130

//in mat4 world_mat;
//in mat4 view_mat;

in vec4 position_in;

void main()
{
    gl_Position = position_in;
}

//version 420 code:

//layout (std140) uniform MatrixBuffer
//{
//    mat4 viewMat;
//    mat4 worldMat;
//};

//in vec3 position;
//
//void main()
//{
//    gl_position = position * worldMat * viewMat;
//}
