#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;

void key_pressed(GLFWwindow * window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint CompileShader(GLuint shaderType, const char * src) {
    GLuint vertShader = glCreateShader(shaderType);
    glShaderSource(vertShader, 1, &src, nullptr);
    glCompileShader(vertShader);

    constexpr auto bufSize = 512;

    GLint ok;
    GLchar infoLog[bufSize];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &ok);

    if (!ok) {
        glGetShaderInfoLog(vertShader, bufSize, nullptr, infoLog);
        std::cerr << "Fatal: Failed to compile shader" << std::endl << infoLog << std::endl;
    }

    return vertShader;
}

GLuint CreateShaderProgram(std::string_view vertFilename, std::string_view fragFilename)  {
    auto getShaderCode = [](std::string_view file) -> std::string {
        std::stringstream ss;
        ss << std::ifstream(file.data()).rdbuf();
        return ss.str();
    };

    const std::string vertCode = getShaderCode(vertFilename);
    const std::string fragCode = getShaderCode(fragFilename);

    auto vertCodeBuf = vertCode.data();

    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertCode.data());
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragCode.data());

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Fatal: Shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}


int main() {
    if (!glfwInit()) {
        std::cerr << "Fatal: Faliled to initialize OpenGL" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow * window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);

    if (!window) {
        std::cerr << "Fatal: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;        
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Fatal: Faliled to initialize GLEW" << std::endl;
        return -1;        
    }
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_pressed);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const auto vert = fs::current_path() / "resources/shaders/triangle.vert";
    const auto frag = fs::current_path() / "resources/shaders/triangle.frag";

    GLuint shaderProgram = CreateShaderProgram(vert.string(), frag.string());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.114f, 0.000f, 0.231f, 1.000f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}