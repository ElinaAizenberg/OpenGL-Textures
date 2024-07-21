#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>


#include "../include/object.h"
#include "../include/loader.h"
#include "../include/utils.h"


Object::Object(const std::string& obj_filepath, const std::string& shader_vert, const std::string& shader_frag): shaderProgram_(shader_vert.c_str(), shader_frag.c_str()) {
    loadObjectFile(obj_filepath);

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &NBO_);

}


void Object::loadObjectFile(const std::string &filepath) {
    if (filepath.empty()){
        return;
    }
    vertices_.clear();
    normals_.clear();

    try{
        ObjectLoader::loadObjFileData(filepath, vertices_, normals_, texture_coordinates_);
    }
    catch(...) {
        std::cerr << "Error: Unable to load file: " << filepath;
        return;
    }
}


void Object::loadObjectBuffers()
{
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * vertices_.size(),
                 vertices_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * normals_.size(),
                 normals_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


}

void Object::draw(glm::mat4 &view, glm::mat4 &projection) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shaderProgram_.use();

    shaderProgram_.setVec4("objectColor", 1, 1, 1, 1);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    shaderProgram_.setMat4("projection", projection);
   shaderProgram_.setMat4("view", view);
   shaderProgram_.setMat4("model", model);


    glBindVertexArray(VAO_);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));
}

Object::~Object() {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &NBO_);
}

void Plane::draw(glm::mat4 &view, glm::mat4 &projection) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shaderProgram_.use();

    shaderProgram_.setVec3("objectColor", 0.741, 0.741, 0.741);
    shaderProgram_.setVec3("lightPos", glm::vec3(15.0f, 15.0f, -10.0));
    shaderProgram_.setVec3("viewPos", glm::vec3(0.0f, 1.0f, 10.0));

    shaderProgram_.setVec3("lightColor", 0.988, 0.945, 0.784);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(angle_), glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.0, 0.0, -6.0));


    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    shaderProgram_.setMat4("projection", projection);
    shaderProgram_.setMat4("view", view);
    shaderProgram_.setMat4("model", model);


    glBindVertexArray(VAO_);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));
    angle_ += 0.5;
}


Earth::Earth(const std::string &obj_filepath, const std::string &shader_vert, const std::string &shader_frag) : Object(
        obj_filepath, shader_vert, shader_frag) {
    glGenBuffers(1, &TBO_);
}

void Earth::loadObjectBuffers() {
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * normals_.size(),
                 normals_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, TBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_coordinates_.size(), texture_coordinates_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void Earth::draw(glm::mat4 &view, glm::mat4 &projection) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Consider using GL_FILL to see the texture

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures_[main_texture_id_].getTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures_[2].getTexture());


    shaderProgram_.use();
    shaderProgram_.setInt("texture2", 1); // Bind to texture unit 0


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(angle_), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    shaderProgram_.setVec3("light.color", light_rgb_[0], light_rgb_[1], light_rgb_[2]);
    shaderProgram_.setVec3("light.direction", glm::vec3(-1.0f, 0.0f, -1.0));
    shaderProgram_.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
    shaderProgram_.setVec3("light.diffuse", diffuse_, diffuse_, diffuse_);

    shaderProgram_.setFloat("clouds_intensity", clouds_intensity_);

    shaderProgram_.setMat4("projection", projection);
    shaderProgram_.setMat4("view", view);
    shaderProgram_.setMat4("model", model);

    glBindVertexArray(VAO_);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));

    glBindVertexArray(0); // Unbind VAO
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

    angle_ += 0.2;
}



