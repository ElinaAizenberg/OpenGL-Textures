
#ifndef PROJECT_4_TEXTURE_H
#define PROJECT_4_TEXTURE_H

#include <iostream>
#include <GL/gl.h>


class Texture{
public:
    GLuint getTexture() const;
protected:
    GLuint texture_id_{0};
};

class Texture2D: public Texture{
public:
    explicit Texture2D(const std::string& filepath);
};

class Texture3D: public Texture{
public:
    explicit Texture3D(const std::vector<std::string>& filepaths);
};
#endif //PROJECT_4_TEXTURE_H
