#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

struct IDrawer;

struct IFigure {
  virtual void Draw(const std::unique_ptr<IDrawer> &drawer) = 0;
};

class Triangle : public IFigure {
private:
  GLsizei _n;

  GLuint _VBO;
  GLuint _VAO;

public:
  Triangle(GLsizei n, GLvoid *vertices, GLsizeiptr size);
  ~Triangle();

  virtual void Draw(const std::unique_ptr<IDrawer> &drawer) override;
};
