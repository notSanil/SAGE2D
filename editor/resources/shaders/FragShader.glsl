#version 330 core

layout (location = 0) in vec4 color;

layout (location = 0) out vec4 FragColor;

void main()
{
	FragColor = color;
}