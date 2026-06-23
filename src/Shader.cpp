#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &vert, const std::string &frag) {
  auto getShaderCode = [](std::string_view file) -> std::string {
    std::stringstream ss;
    ss << std::ifstream(file.data()).rdbuf();
    return ss.str();
  };

  const std::string vertCode = getShaderCode(vert);
  const std::string fragCode = getShaderCode(frag);

  GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertCode.data());
  GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragCode.data());

  _program = glCreateProgram();
  glAttachShader(_program, vertShader);
  glAttachShader(_program, fragShader);

  glLinkProgram(_program);

  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_program, 512, nullptr, infoLog);
    std::cerr << "Fatal: Shader program linking failed\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}

GLuint Shader::CompileShader(GLuint shaderType, const char *src) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  constexpr auto bufSize = 512;

  GLint ok;
  GLchar infoLog[bufSize];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

  if (!ok) {
    glGetShaderInfoLog(shader, bufSize, nullptr, infoLog);
    std::cerr << "Fatal: Failed to compile shader" << std::endl
              << infoLog << std::endl;
  }

  return shader;
}
