#version 330

uniform sampler2D tex0;

in vec2 i_tc;
in float i_att;

out vec4 pixelColor;

void main(void) 
{
	vec4 color = texture(tex0, i_tc);
	pixelColor = vec4(color.rgb * i_att, color.a);
}
