
#ifndef PROJECT_4_TEXTURE_H
#define PROJECT_4_TEXTURE_H

#include <iostream>
#include <GL/gl.h>


class Texture{
public:
    explicit Texture(const std::string& filepath);
    GLuint getTexture() const;

private:
    GLuint texture_id_{0};



};

#endif //PROJECT_4_TEXTURE_H
