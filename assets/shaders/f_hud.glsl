#version 330

uniform sampler2D tex;

in vec2 i_tc;

out vec4 pixelColor;

void main(void)
{
	pixelColor = texture(tex, i_tc);
}
