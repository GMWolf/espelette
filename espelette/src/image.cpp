//
// Created by felix on 06/10/2021.
//

#include <image.h>
#include <stb_image.h>

#include <glad/gl.h>

Image *createImage(uint16_t width, uint16_t height, ImageFiltering filtering, size_t channels, void* data)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (filtering == ImageFiltering::Linear)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    GLenum format;
    switch (channels) {
        case 1:
            format = GL_RED;
            break;
        case 2:
            format = GL_RG;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            assert(false);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    return new Image {
            .width = static_cast<uint16_t>(width),
            .height = static_cast<uint16_t>(height),
            .handle = static_cast<uint16_t>(texture)
    };
}

Image *loadImage(const char *path, ImageFiltering filtering) {
    int width, height, channels;
    stbi_uc *data = stbi_load(path, &width, &height, &channels, 0);

    Image* image = createImage(width, height, filtering, channels, data);

    stbi_image_free(data);

    return image;
}

void freeImage(Image *image)
{
    glDeleteTextures(1, &image->handle);
    delete image;
}