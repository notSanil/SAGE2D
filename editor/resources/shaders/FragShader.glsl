#version 430 core

layout (location = 0) in vec4 color;
layout (location = 1) in vec2 TexCoords;

layout (location = 0) out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, TexCoords) * color;
}