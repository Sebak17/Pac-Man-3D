
#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../../libs/lodepng.h"

namespace Game {

	using namespace std;
	using namespace glm;

	class Loader {
		public:
			Loader();
			virtual ~Loader();

			GLuint readTexture(const char* filename);
	};

}

#endif