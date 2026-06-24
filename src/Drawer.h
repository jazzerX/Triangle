#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct IDrawer {
  virtual void Draw(GLuint VAO) = 0;
  virtual ~IDrawer() {};
};

class DynamicColorDraw : public IDrawer {
class PulsatingDrawer : public IDrawer {
private:
  GLuint _shaderProgram;

public:
  PulsatingDrawer(GLuint shaderProgram) : _shaderProgram(shaderProgram) {};

  virtual void Draw(GLuint VAO) override;
};
