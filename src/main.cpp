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

#include "map/TileFloor.h"
#include "map/TileWall.h"

#include "Entity/Ghost.h"

GLuint textureWall, textureFloor;

Game::Loader gameLoader;
Game::Camera camera;

std::vector<Map::TileFloor> floors;
std::vector<Map::TileWall> walls;

std::vector<Entity::Ghost> ghosts;

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

	textureWall = gameLoader.readTexture("assets/textures/bricks.png");
	textureFloor = gameLoader.readTexture("assets/textures/stone-wall.png");


	for (int i = 0; i < 3; i++) {
		Entity::Ghost ghost(textureFloor, glm::vec3(i * 8.9f, 0.0f, 0.0f));
		ghosts.push_back(ghost);
	}

	

	for (int i = 0; i < 10; i++) {
		Map::TileFloor floor(textureFloor, glm::vec3(i * 2.0f, 0.0f, 0.0f));
		floors.push_back(floor);
	}

	for (int x = 0; x < 10; x++) {
		for (int z = 0; z < 10; z++) {
			Map::TileFloor floor(textureFloor, glm::vec3(x * 2.0f, 0.0f, z * 2.0f));
			floors.push_back(floor);
		}
	}


	for (int x = 0; x < 10; x++) {
		Map::TileWall wall(textureWall, glm::vec3(x * 2.0f, 0.0f, 0.0f), Map::WallDirection::WEST);
		walls.push_back(wall);
	}


	for (int z = 0; z < 10; z++) {
		Map::TileWall wall(textureWall, glm::vec3(18.0f, 0.0f, z * 2.0f), Map::WallDirection::NORTH);
		walls.push_back(wall);
	}

	for (int x = 0; x < 10; x++) {
		Map::TileWall wall(textureWall, glm::vec3(x * 2.0f, 0.0f, 18.0f), Map::WallDirection::EAST);
		walls.push_back(wall);
	}

	for (int z = 0; z < 10; z++) {
		Map::TileWall wall(textureWall, glm::vec3(0, 0.0f, z * 2.0f), Map::WallDirection::SOUTH);
		walls.push_back(wall);
	}

}


void freeOpenGLProgram(GLFWwindow* window)
{
	freeShaders();

	glDeleteTextures(1, &textureWall);
	glDeleteTextures(2, &textureFloor);
}

void update(float deltaTime)
{
	camera.update();

	for (auto& ghost : ghosts) {
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

	for (auto& ghost : ghosts) {
		ghost.draw(spLambert, M);
	}



	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));

	for (auto& floor : floors) {
		floor.draw(spTextured, M);
	}

	for (auto& wall : walls) {
		wall.draw(spTextured, M);
	}
	


	/*
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));

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
	*/


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
