#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "constants.h"
#include "shaderprogram.h"
#include "math.h"
#include "cmath"

#include "Game/Loader.h"
#include "Game/Camera.h"

Game::MapData mapData;

Game::Loader gameLoader;
Game::Camera camera(mapData);

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	camera.move(key, action);
}

void initOpenGLProgram(GLFWwindow* window)
{
	initShaders();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, keyCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	gameLoader.loadTextures();

	mapData = gameLoader.loadMap("assets/game.json");

}


void freeOpenGLProgram(GLFWwindow* window)
{
	freeShaders();

	gameLoader.destroyTextures();
}

void update(float deltaTime)
{
	camera.update();

	for (auto& ghost : mapData.ghosts) {
		ghost.move(deltaTime);
	}
	
}


void drawScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 V = camera.getV();
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 2.0f, 0.1f, 50.0f);
	glm::mat4 M = glm::mat4(1.0f);


	glm::mat4 M_1 = glm::translate(M, glm::vec3(-10.0f, 0.0f, -10.0f));
	
	
	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	for (auto& ghost : mapData.ghosts) {
		ghost.draw(spLambert, M);
	}

	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));

	for (auto& floor : mapData.floors) {
		floor.draw(spTextured, M);
	}

	for (auto& wall : mapData.walls) {
		wall.draw(spTextured, M);
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
		float deltaTime = (float) glfwGetTime();

        glfwSetTime(0);

		update(deltaTime);

		drawScene(window);

		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
