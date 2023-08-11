#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 colour;

out vec4 outColour;

void main()
{
	vec4 texel=texture(tex,texCoord);
	outColour=vec4(texel.xyz*colour,texel.w);
}