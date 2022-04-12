#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec3 lights;

layout (location=0) in vec4 vertex;
layout (location=2) in vec2 texCoord;


out vec2 i_tc;
out float i_nl;

void main(void) {
    gl_Position = P * V * M * vertex;

    float d = distance(M * vertex, vec4(0, 0, 0, 1));

    float att = -0.25f + (0.01f * d) + (0.002f * d * d);

    i_tc = texCoord;
    //i_nl = -att;
    i_nl = 1;
}
