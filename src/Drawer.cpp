#include "Drawer.h"
#include <cmath>

void DynamicColorDraw::Draw(GLuint VAO) {
  GLfloat currTime = glfwGetTime();
  GLfloat r = (sin(currTime) / 2) + 0.5;
  GLfloat g = 0.0f;
  GLfloat b = 0.0f;
  GLfloat w = 1.0f;

  GLint vertexColorLocation =
      glGetUniformLocation(_shaderProgram, "vertexColor");

  glUseProgram(_shaderProgram);
  glUniform4f(vertexColorLocation, r, g, b, w);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}
