#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <irrKlang.h>

#include "shaderprogram.h"
#include "Game/Camera.h"
#include "Game/GameManager.h"
#include "Game/Loader.h"
#include "Game/Player.h"
#include "Map/MapManager.h"

irrklang::ISoundEngine* engine;

Game::MapData mapData;

Map::MapManager mapManager;
Game::GameManager gameManager;

Game::Player player;
Game::Loader gameLoader(mapManager);
Game::Camera camera(mapManager, mapData);


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

	if (gameManager.status == Game::Status::MENU) {

		if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) {
			gameManager.status = Game::Status::PLAYING;
		}

	}

	if (gameManager.status == Game::Status::PLAYING) {

		camera.move(key, action);

	}

}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	camera.moveMouse((float) xPos, (float) yPos);
}

void initOpenGLProgram(GLFWwindow* window)
{
	engine = irrklang::createIrrKlangDevice();

	initShaders();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);

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

	if (gameManager.status == Game::Status::PLAYING) {

		camera.update();

		for (auto& ghost : mapData.ghosts) {
			ghost.move(deltaTime);
		}

		for (auto& coin : mapData.coins) {
			coin.update(deltaTime);
		}

		if (camera.checkGhostsCollisions() && !player.isProtected()) {
			player.addProtection();
			player.livesCount--;
			printf("GHOST!!! Lives: %d\n", player.livesCount);
			engine->play2D("assets/sounds/ghost.wav", false);
		}

		if (camera.checkCoinsCollisions()) {
			player.points++;
			printf("Points: %d\n", player.points);
			engine->play2D("assets/sounds/bleep.wav", false);
		}

		if (player.livesCount <= 0) {
			gameManager.status = Game::Status::DEFAT;
		}

		if (player.points == mapData.coins.size()) {
			//gameManager.status = Game::Status::VICTORY;
		}
	}

}


void drawScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 V = camera.getV();
	glm::mat4 P = glm::perspective(glm::radians(50.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 50.0f);
	glm::mat4 M = glm::mat4(1.0f);

	if (gameManager.status == Game::Status::PLAYING)
	{
		
		spLambert->use();
		glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
		glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

		for (auto& ghost : mapData.ghosts) {
			ghost.draw(spLambert, M);
		}

		for (auto& coin : mapData.coins) {
			coin.draw(spLambert, M);
		}


		spMap->use();
		glUniformMatrix4fv(spMap->u("P"), 1, false, glm::value_ptr(P));
		glUniformMatrix4fv(spMap->u("V"), 1, false, glm::value_ptr(V));

		for (auto& floor : mapManager.floors) {
			floor.draw(spMap, M);
		}

		for (auto& wall : mapManager.walls) {
			wall.draw(spMap, M);
		}

		for (auto& torch : mapManager.torches) {
			torch.draw(spMap, M);
		}

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

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man 3D", NULL, NULL);

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
