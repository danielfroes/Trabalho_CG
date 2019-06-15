#version 330 core
out vec4 FragColor;
in vec3 ourColor; //alteração para adicionar cor aos triangulos

void main()
{
   FragColor = vec4(ourColor, 1.0f); //frag color recebe como input a cor do vertice
}