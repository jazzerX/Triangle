#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/gltypes.h>

#include <iostream>
#include <filesystem>

#include "Figure.h"
#include "Drawer.h"
#include "Shader.h"

namespace fs = std::filesystem;

void key_pressed(GLFWwindow * window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
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

    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0,
        -0.5f, -0.5f, 0.0,
         0.5f, -0.5f, 0.0
    };

    const auto vert = fs::current_path() / "resources/shaders/triangle.vert";
    const auto frag = fs::current_path() / "resources/shaders/triangle.frag";
    Shader shaderProgram = Shader(vert.string(), frag.string());

    Triangle t(1, vertices, sizeof(vertices));
    // TODO: press 1, 2, 3, etc to change drawing type
    std::unique_ptr<IDrawer> d = std::make_unique<PulsatingDrawer>(shaderProgram.GetPogram());

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.114f, 0.000f, 0.231f, 1.000f);
        glClear(GL_COLOR_BUFFER_BIT);

        t.Draw(d);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}