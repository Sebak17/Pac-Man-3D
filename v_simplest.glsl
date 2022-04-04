#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu

in vec4 colors;

out vec4 iC;

void main(void) {

	gl_Position = P * V * M * vertex;

	float d = distance(V * M * vertex, vec4(0, 0, 0, 1));

	d = 1 - ((d - 3.3) / 1.7);

	iC = colors * d;
}

