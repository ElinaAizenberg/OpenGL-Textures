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

    Earth earth = Earth("../objects/earth.obj", "../shaders/earth.vert", "../shaders/earth.frag");
    earth.loadObjectBuffers();
    Plane plane = Plane("../objects/14082_WWII_Plane_Japan_Kawasaki_Ki-61_v1_L2.obj", "../shaders/plane.vert", "../shaders/plane.frag");
    plane.loadObjectBuffers();
    Skybox skybox = Skybox("../shaders/skybox.vert", "../shaders/skybox.frag");

    while (!glfwWindowShouldClose(window))
    {
        drawingLib.getWindowSize(window);
        drawingLib.drawScene(window, plane, earth, skybox);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

