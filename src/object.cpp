#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "../include/object.h"
#include "../include/loader.h"


Object::Object(const std::string& obj_filepath, const std::string& shader_vert, const std::string& shader_frag): shaderProgram_(shader_vert.c_str(), shader_frag.c_str()) {
    loadObjectFile(obj_filepath);

    // generates a single Vertex Array Object (VAO)  that stores the state needed to supply vertex data,
    // including information about vertex attribute pointers: position, normals, text.coordinates etc.
    glGenVertexArrays(1, &VAO_);
    // generates a single Vertex Buffer Object (VBO) that stores the actual vertex data.
    glGenBuffers(1, &VBO_);
    // buffer for normals
    glGenBuffers(1, &NBO_);
}

void Object::loadObjectFile(const std::string &filepath)
/** Loads vertices, normals and texture coodinates from an .obj file using Loader class. */
{
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
/** Loads data into all Object's buffers: vertices, normals. */
{
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * vertices_.size(),
                 vertices_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enables the vertex attribute array at the specified index (0 corresponds to the vertex positions) within the currently bound VAO.
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * normals_.size(),
                 normals_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // the specified index 1 corresponds to the vertex normal within the currently bound VAO.
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Object::draw(glm::mat4 &view, glm::mat4 &projection)
/** Default drawing function. */
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shaderProgram_.use();

    shaderProgram_.setVec4("objectColor", 1, 1, 1, 1);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    shaderProgram_.setMat4("projection", projection);
    shaderProgram_.setMat4("view", view);
    shaderProgram_.setMat4("model", model);

    glBindVertexArray(VAO_);
    // draws the specified number of triangles using the vertex data that has been previously bound to the vertex array object (VAO)
    // The difference from glDrawElements is that it uses an index buffer to specify the order in which vertices should be drawn.
    // While with glDrawArrays vertices are rendered sequentially from the vertex array without any reuse or indexing.
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));
}

Object::~Object()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &NBO_);
}

void Plane::draw(glm::mat4 &view, glm::mat4 &projection)
/** Render a model of plane with custom color, rotation and scaling. */
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shaderProgram_.use();
    // set uniforms to calculate lighting in fragment shader
    shaderProgram_.setVec3("objectColor", 0.741, 0.741, 0.741);
    shaderProgram_.setVec3("lightPos", glm::vec3(15.0f, 15.0f, 10.0));
    shaderProgram_.setVec3("viewPos", glm::vec3(0.0f, 1.0f, 10.0));

    shaderProgram_.setVec3("lightColor", 0.988, 0.945, 0.784);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(angle_), glm::vec3(0.0, 1.0, 0.0));
    model = glm::translate(model, glm::vec3(0.0, 0.0, -6.0));

    model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    shaderProgram_.setMat4("projection", projection);
    shaderProgram_.setMat4("view", view);
    shaderProgram_.setMat4("model", model);

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));

    // rotation angle changes every frame to make plane 'fly' around Earth model.
    angle_ += 0.5;
}

Earth::Earth(const std::string &obj_filepath, const std::string &shader_vert, const std::string &shader_frag) : Object(
        obj_filepath, shader_vert, shader_frag)
{
    // buffer for texture coordinates
    glGenBuffers(1, &TBO_);
}

void Earth::loadObjectBuffers()
/** Loads data into all Object's buffers: vertices, normals, texture coordinates. */
{
    // load data into buffers for vertex positions and normals
    Object::loadObjectBuffers();
    glBindVertexArray(VAO_);

    // load buffer with texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, TBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_coordinates_.size(), texture_coordinates_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    // vertex attributes with indexes 0 and 1 are assigned to vertex position and normal
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Earth::draw(glm::mat4 &view, glm::mat4 &projection)
/** Render a model of Earth with a combination of 2 textures: Earth texture (day or night) and clouds texture.*/
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // using GL_FILL to see the texture

    glActiveTexture(GL_TEXTURE0);
    // bind to main Earth texture (daylight or night)
    // This texture is used as diffuse map for lighting calculations
    glBindTexture(GL_TEXTURE_2D, textures_[main_texture_id_].getTexture());

    glActiveTexture(GL_TEXTURE1);
    // bind to clouds texture
    glBindTexture(GL_TEXTURE_2D, textures_[2].getTexture());

    shaderProgram_.use();
    // assign Earth texture unit to the Material.diffuse uniform sampler
    shaderProgram_.setInt("material.diffuse", 0);

    // texture1 with clouds is set with a separate uniform sampler2D,
    // while main Earth texture is set as sampler2D diffuse map within Material struct
    shaderProgram_.setInt("texture1", 1);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(angle_), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(scale_, scale_, scale_));

    // set light parameters for the active shader program
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

    // rotation angle changes every frame to make Earth rotate around the center.
    angle_ += 0.2;
}

Skybox::Skybox(const std::string& shader_vert, const std::string& shader_frag): shaderProgram_(shader_vert.c_str(), shader_frag.c_str()){
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    // consider all vertex positions of the cube to be its texture coordinates when sampling a cubemap.
    // Therefore, we need only 1 buffer with vertices' coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * vertices_.size(),
                 vertices_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Skybox::draw(glm::mat4 &view, glm::mat4 &projection)
/** Render a skybox with cubemap texture. */
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // in vertex shader z-coordinate of skybox is set to w-value, so that depth testing results in 1.0.
    // The depth buffer is filled with 1.0 for the skybox, so to make sure the skybox passes the depth tests
    // with values less than or equal to the depth buffer, depth test function is set to  GL_LEQUAL.
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    // bind to generated cubemap texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture_.getTexture());

    shaderProgram_.use();
    shaderProgram_.setInt("skybox", 0);

    // Cubemap is meant to creat an impression that is large, static and always far away from viewer.
    // The cube should not move with viewer.
    // This trick removes any translation, but keeps all rotation transformations so the user can still look around the scene.
    glm::mat4 new_view = glm::mat4(glm::mat3(view));

    shaderProgram_.setMat4("projection", projection);
    shaderProgram_.setMat4("view", new_view);

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()/3));

    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth testing function back to 'less than'.
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind texture
}
