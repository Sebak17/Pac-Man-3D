#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 torch[3];

in vec4 vertex;
in vec2 texCoord;
in vec4 normal;


out vec2 i_tc;
out float i_att;

void main(void) 
{
    gl_Position = P * V * M * vertex;

    float d = 9999999;
    for (int i = 0; i < 3 ; i++)
    {
        float dt = distance(M * vertex, torch[i]);
        if (dt < d) d = dt;
    }

    float light = -0.25f + (0.01f * d) + (0.00025f * d * d);

    i_tc = texCoord;
    i_att = -light;
}
