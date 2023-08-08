#version 330 core

in vec2 textureCoord;

uniform sampler2D tex;

out vec4 fragColour;

void main()
{
	fragColour=texture(tex,textureCoord);
}