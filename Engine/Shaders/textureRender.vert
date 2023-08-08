#version 330 core

layout(location=0) in vec2 vertexPosition;

out vec2 textureCoord;

void main()
{
	textureCoord=vertexPosition;

	gl_Position=vec4(vertexPosition*2-1,0,1);
}