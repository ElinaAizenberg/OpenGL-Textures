#ifndef PROJECT_4_DRAWING_LIB_H
#define PROJECT_4_DRAWING_LIB_H
#include <GLFW/glfw3.h>

#include "../include/object.h"


class DrawingLib{
public:
    DrawingLib() = default;
    GLFWwindow* createWindow() const;
    void getWindowSize(GLFWwindow* window);

    void drawScene(GLFWwindow* window, Plane& plane, Earth& earth);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void defineCallbackFunction(GLFWwindow* window);



private:

    int window_width_{1920};
    int window_height_{1080};

    bool switch_time_{false};

    glm::vec3 camera_position_= glm::vec3(0.0f, 1.0f, 10.0);
    glm::vec3 target_position_ = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up_direction_ = glm::vec3(0.0f, 1.0f, 0.0f);


    };

#endif //PROJECT_4_DRAWING_LIB_H
