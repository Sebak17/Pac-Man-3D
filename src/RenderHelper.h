#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include <glm/gtc/type_ptr.hpp>
#include "shaderprogram.h"

void renderObjectWithSingleTexture(ShaderProgram* shaderProgram, glm::mat4 M, float* vertCoords, float* texCoords, int vertexCount, GLuint texture);
void renderObjectWithColor(ShaderProgram* shaderProgram, glm::mat4 M, float* vertCoords, float* normalCoords, float* texCoords, int vertexCount, float colorRed, float colorGreen, float colorBlue);

#endif
