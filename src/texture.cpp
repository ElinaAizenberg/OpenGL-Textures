#include <glad/glad.h>
#include <vector>

#include "../include/texture.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


Texture2D::Texture2D(const std::string& filepath)
/** Generates an OpenGL texture object, sets its wrapping and filtering parameters,
 loads the texture data from the specified file, and applies it to the texture object. */
{
    // Generate a texture object and store its ID
    glGenTextures(1, &texture_id_);

    // Bind the generated texture object to the 2D texture target
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    // Set texture wrapping parameters:
    // GL_CLAMP_TO_EDGE ensures texture coordinates outside the 0.0 to 1.0 range  will be clamped to the edge of the texture.
    // Coordinates s, t (and r if you're using 3D textures) equivalent to x,y,z.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set texture filtering parameters:
    // GL_LINEAR_MIPMAP_LINEAR uses linear filtering for both the texture and mipmaps, which provides smooth transitions between mipmap levels.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Variables to store the dimensions and number of color channels in the texture image
    int width, height, nrChannels;

    // Flip the texture vertically when loading
    stbi_set_flip_vertically_on_load(true);

    // Load the image data from the specified file
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        // Create the texture image in OpenGL using the loaded data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Generate mipmaps for the texture for better scaling and rendering at different distances.
        // Mipmaps is a collection of texture images where each subsequent texture is twice as small compared to the previous one.
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // Free the image memory as it's now loaded into OpenGL
    stbi_image_free(data);

    // Unbind the texture to prevent unintended modifications
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTexture() const
/** Returns texture ID.*/
{
    return texture_id_;
}

Texture3D::Texture3D(const std::vector<std::string>& filepaths)
/** Sets up a 3D texture (cube map) in OpenGL, loading six individual images to represent the six faces of a cube,
and configures the necessary filtering and wrapping options.*/
{
    glGenTextures(1, &texture_id_);
    // Bind the generated texture object to the cube map target
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < filepaths.size(); i++)
    {
        unsigned char *data = stbi_load(filepaths[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            // Determine the image format based on the number of channels
            GLenum format = 0;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            // Create the texture image for the current face of the cube map
            // GL_TEXTURE_CUBE_MAP_POSITIVE_X + i selects the appropriate face of the cube map
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            // Set texture filtering parameters for the cube map
            // GL_LINEAR takes an interpolated value from the texture coordinate's neighboring texels, approximating a color between the texels.
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Set texture wrapping parameters for the cube map
            // Cube maps require wrapping along three axes: S, T, and R
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << filepaths[i] << std::endl;
            stbi_image_free(data);
        }
    }
}