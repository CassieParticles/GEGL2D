#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 colour;

out vec4 outColour;

void main()
{
	float texel=texture(tex,texCoord).x;
	outColour=vec4(vec3(texel)*colour,texel);
}