#version 330

uniform sampler2D tex0;

out vec4 pixelColor;

in vec2 i_tc;
in float i_att;

void main(void) 
{
	vec4 color = texture(tex0, i_tc);
	pixelColor = vec4(color.rgb * i_att, color.a);
}
