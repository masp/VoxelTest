#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 mvp;

out vec2 UV;

void main()
{
	gl_Position = mvp * position;

	UV = texCoords;
}
