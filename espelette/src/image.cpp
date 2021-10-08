//
// Created by felix on 06/10/2021.
//

#include "image.h"
#include <stb_image.h>

#include <glad/gl.h>

Image *loadImage(const char *path)
{
    int width, height, channels;
    stbi_uc* data = stbi_load(path, &width, &height, &channels, 4);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return new Image {
        .width = static_cast<uint16_t>(width),
        .height = static_cast<uint16_t>(height),
        .handle = static_cast<uint16_t>(texture)
    };
}

void freeImage(Image *image)
{
    glDeleteTextures(1, &image->handle);
    delete image;
}