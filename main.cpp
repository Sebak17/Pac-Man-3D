#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "math.h"
#include "cmath"

#include "Camera.h"

#include "map/TileFloor.h"
#include "map/TileWall.h"

GLuint textureWall, textureFloor;

Game::Camera camera;

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	camera.move(key, action);

}

GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void initOpenGLProgram(GLFWwindow* window)
{
	initShaders();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, keyCallback);

	textureWall = readTexture("assets/textures/bricks.png");
	textureFloor = readTexture("assets/textures/stone-wall.png");
}


void freeOpenGLProgram(GLFWwindow* window)
{
	freeShaders();

	glDeleteTextures(1, &textureWall);
	glDeleteTextures(2, &textureFloor);
}

void drawScene(GLFWwindow* window, float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update();


	glm::mat4 V = camera.getV();

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 2.0f, 0.1f, 50.0f);



	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));


	glm::mat4 M_1 = glm::mat4(1.0f);

	M_1 = glm::translate(M_1, glm::vec3(-10.0f, 0.0f, -10.0f));



	

	for (int x = 0; x < 10; x++) {

		{
			glm::mat4 M_W = glm::rotate(M_1, 90 * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M_W));
			Map::tileWall.draw(textureWall);
		}

		for (int z = 0; z < 10; z++) {

			glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M_1));
			Map::tileFloor.draw(textureFloor);

			M_1 = glm::translate(M_1, glm::vec3(2.0f, 0.0f, 0.0f));
		}

		{
			glm::mat4 M_W = glm::rotate(M_1, 90 * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M_W));
			Map::tileWall.draw(textureWall);
		}

		M_1 = glm::translate(M_1, glm::vec3(10 * -2.0f, 0.0f, 2.0f));
	}


    glfwSwapBuffers(window);
}


int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(1600, 800, "Pac-Man 3D", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window))
	{

		float deltaTime = glfwGetTime();

        glfwSetTime(0);

		drawScene(window, deltaTime);

		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
