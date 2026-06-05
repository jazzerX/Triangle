#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

#include <iostream>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Fatal: Faliled to initialize OpenGL" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Fatal: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;        
    }

    glewExperimental = GL_TRUE;
    if (!glewInit()) {
        std::cerr << "Fatal: Faliled to initialize GLEW" << std::endl;
        return -1;        
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}