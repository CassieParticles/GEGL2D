#version 330 core

layout(location=0) in vec2 vertexPosition;

layout(std140) uniform windowData
{
	ivec2 screenSize;
};

uniform vec2 position;
uniform vec2 size;

uniform vec2 relativeTo;

void main()
{

	vec2 scaledPos=position/screenSize;	//Get the position and size in 0-1 scale of the screen
	vec2 scaledSize=size/screenSize;

	vec2 normRelTo=relativeTo/1024.f;	//Get the relative to position scaled between 0-1

	vec2 screenPos=scaledPos+normRelTo;	//Get the top left corner position between 0-1
	vec2 offset=vertexPosition*scaledSize;

	screenPos=screenPos*2-1;	//Rescale position to be between -1 and 1
	offset*=2;

	gl_Position=vec4(screenPos+offset,0,1);
}