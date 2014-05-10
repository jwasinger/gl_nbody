#version 420

layout (std140) uniform MatrixBuffer
{
    mat4 viewMat;
    mat4 worldMat;
};

in vec3 position;

void main()
{
    gl_position = position * worldMat * viewMat;
}
