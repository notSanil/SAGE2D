#version 430 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 col;
layout (location = 2) in vec2 texCoords;

layout (location = 0) uniform mat4 projection;

layout (location = 0) out vec4 color;
layout (location = 1) out vec2 TexCoords;
void main()
{
	gl_Position = projection * vec4(pos, 1.0, 1.0);

	color = col;
	TexCoords = texCoords;
}