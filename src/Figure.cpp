#include "Figure.h"
#include "Drawer.h"

Triangle::Triangle(GLsizei n, GLvoid *vertices, GLsizeiptr size) : _n(n) {
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  glGenBuffers(1, &_VBO);

  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

Triangle::~Triangle() {
  glDeleteVertexArrays(_n, &_VAO);
  glDeleteBuffers(_n, &_VBO);
}

void Triangle::Draw(const std::unique_ptr<IDrawer> &drawer) {
  drawer->Draw(_VAO);
}
