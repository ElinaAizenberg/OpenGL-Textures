#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "../include/drawing_lib.h"


int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    DrawingLib drawingLib = DrawingLib();

    GLFWwindow* window = drawingLib.createWindow();
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    drawingLib.defineCallbackFunction(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Earth earth = Earth("/home/elina/MyProjects/object_files/earth.obj", "/home/elina/MyProjects/OpenGl/project_4/shaders/earth.vert", "/home/elina/MyProjects/OpenGl/project_4/shaders/earth.frag");
    earth.loadObjectBuffers();
    Plane plane = Plane("/home/elina/MyProjects/object_files/f-5.obj", "/home/elina/MyProjects/OpenGl/project_4/shaders/plane.vert", "/home/elina/MyProjects/OpenGl/project_4/shaders/plane.frag");
    plane.loadObjectBuffers();

    while (!glfwWindowShouldClose(window))
    {
        drawingLib.getWindowSize(window);
        drawingLib.drawScene(window, plane, earth);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

