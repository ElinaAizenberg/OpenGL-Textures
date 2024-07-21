#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/drawing_lib.h"

GLFWwindow *DrawingLib::createWindow() const {
    return glfwCreateWindow(window_width_, window_height_, "OpenGL Project 3", nullptr, nullptr);
}

void DrawingLib::getWindowSize(GLFWwindow *window) {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    window_width_  = w;
    window_height_ = h;
}

void DrawingLib::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_1){
            switch_time_ = true;
        }
    }
}

void DrawingLib::defineCallbackFunction(GLFWwindow* window)
/** Sets up callback functions for a GLFW window.*/
{
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto* drawing_lib = static_cast<DrawingLib*>(glfwGetWindowUserPointer(win));
        drawing_lib->keyCallback(win, key, scancode, action, mods);
    });
}

void DrawingLib::drawScene(GLFWwindow *window, Plane& plane, Earth& earth) {
    if (switch_time_){
        earth.switchTime();
        switch_time_ = false;
    }


    glViewport(0, 0, window_width_, window_height_);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection_mat = glm::perspective(glm::radians(65.0f), (float)window_width_ / (float)window_height_, 0.1f, 100.0f);

    glm::mat4 view_mat = glm::lookAt(camera_position_, target_position_, up_direction_);
    plane.draw(view_mat, projection_mat);
    earth.draw(view_mat, projection_mat);


    glfwSwapBuffers(window);
    glfwPollEvents();
}

