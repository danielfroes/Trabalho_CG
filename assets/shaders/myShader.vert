#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform mat4 transform; //passa do código principal para o shader


void main()
{
    gl_Position = transform * vec4(aPos, 1.0f); //a multiplicação de matrizes é feita no vertex shader
    ourColor = aColor;
}