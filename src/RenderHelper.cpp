#include "RenderHelper.h"

void renderObjectWithSingleTexture(ShaderProgram* shaderProgram, glm::mat4 M, float* vertCoords, float* texCoords, float* normalCoords, int vertexCount, GLuint texture)
{
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(shaderProgram->a("vertex"));
	glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, vertCoords);

	glEnableVertexAttribArray(shaderProgram->a("normal"));
	glVertexAttribPointer(shaderProgram->a("normal"), 4, GL_FLOAT, false, 0, normalCoords);

	glEnableVertexAttribArray(shaderProgram->a("texCoord"));
	glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shaderProgram->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(shaderProgram->a("vertex"));
}

void renderObjectWithSingleTexture(ShaderProgram* shaderProgram, glm::mat4 M, float* vertCoords, float* texCoords, int vertexCount, GLuint texture)
{
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(shaderProgram->a("vertex"));
	glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, vertCoords);

	glEnableVertexAttribArray(shaderProgram->a("texCoord"));
	glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);

	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shaderProgram->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(shaderProgram->a("vertex"));
}

void renderObjectWithColor(ShaderProgram* shaderProgram, glm::mat4 M, float* vertCoords, float* normalCoords, float* texCoords, int vertexCount, float colorRed, float colorGreen, float colorBlue)
{
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));
	glUniform4f(spLambert->u("color"), colorRed, colorGreen, colorBlue, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertCoords);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normalCoords);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}