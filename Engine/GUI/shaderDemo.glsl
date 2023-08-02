#version 330 core

layout(location=0) in vec2 vertexPosition;

uniform vec2 position;
uniform vec2 size;

void main()
{
	vec2 tl=position/1024.0;	//Get the position from 0-1
	vec2 offset=size/1024.0;

	tl=tl*2-1;	//rescale to be between -1 - 1
	offset=offset*2-1;

	gl_Position=vec4(tl+offset,0,1);
}