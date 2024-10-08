
#ifndef PROJECT_4_OBJECT_H
#define PROJECT_4_OBJECT_H

#include <string>
#include <vector>

#include "../include/texture.h"
#include "../include/shader.h"

class Object{
public:
    Object(const std::string& obj_filepath, const std::string& shader_vert, const std::string& shader_frag);
    ~Object();

    virtual void loadObjectBuffers();
    virtual void draw(glm::mat4& view, glm::mat4& projection);
    void loadObjectFile(const std::string& filepath);

protected:
    float scale_{1};

    std::vector<GLfloat> vertices_{};
    std::vector<GLfloat> normals_{};
    std::vector<GLfloat> texture_coordinates_{};

    GLuint VAO_{};
    GLuint VBO_{};
    GLuint NBO_{};

    ShaderProgram shaderProgram_;

};

class Plane : public Object{
public:
    Plane(const std::string& obj_filepath, const std::string& shader_vert, const std::string& shader_frag) : Object(obj_filepath, shader_vert, shader_frag){}
    void draw(glm::mat4 &view, glm::mat4 &projection) override;

private:
    float angle_{0.5};
    float scale_{1};
};

class Earth : public Object{
public:
    Earth(const std::string& obj_filepath, const std::string& shader_vert, const std::string& shader_frag);
    void draw(glm::mat4 &view, glm::mat4 &projection) override;
    void loadObjectBuffers() override;
    void switchTime()
    {
        main_texture_id_ ^= 1;
        if (main_texture_id_ == 1){
            clouds_intensity_ = 0.01;
            light_rgb_[0] = 0.98;
            light_rgb_[1] = 0.859;
            light_rgb_[2] = 0.0;

        } else {
            clouds_intensity_ = 0.25;
            light_rgb_[0] = 0.98;
            light_rgb_[1] = 0.945;
            light_rgb_[2] = 0.784;
        }
    }

private:
    float scale_{2};
    GLuint TBO_{};
    float angle_{0.2};

    std::vector<Texture2D> textures_ = {Texture2D("../textures/8k_earth_daymap.jpg"),
                                        Texture2D("../textures/8k_earth_nightmap.jpg"),
                                        Texture2D("../textures/8k_earth_clouds.jpg")};

    int main_texture_id_{0};

    float light_rgb_[3] = {0.988, 0.945, 0.784};
    float clouds_intensity_ = 0.25f;
    float diffuse_ = 1.0f;

};

class Skybox {
public:
    Skybox(const std::string& shader_vert, const std::string& shader_frag);
    void draw(glm::mat4 &view, glm::mat4 &projection);

private:
    GLuint VAO_{};
    GLuint VBO_{};
    ShaderProgram shaderProgram_;

    Texture3D skybox_texture_ = Texture3D({"../textures/sky/right.jpg",
                                           "../textures/sky/left.jpg",
                                           "../textures/sky/top.jpg",
                                           "../textures/sky/bottom.jpg",
                                           "../textures/sky/back.jpg",
                                           "../textures/sky/front.jpg"});

    std::vector<GLfloat> vertices_ =
            {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

};


#endif //PROJECT_4_OBJECT_H
