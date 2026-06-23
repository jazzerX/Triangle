#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader {
private:
  GLuint _program;

public:
  Shader(const std::string &vert, const std::string &frag);
  ~Shader() = default;

  [[nodiscard]]
  GLuint GetPogram() { return _program; };

  void Use();

private:
  GLuint CompileShader(GLuint shaderType, const char *src);
};
