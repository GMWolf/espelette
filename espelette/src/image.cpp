//
// Created by felix on 06/10/2021.
//

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/gl.h>

Image *loadImage(const char *path)
{
    int width;
    int height;
    int channels;
    stbi_uc* imageData = stbi_load(path, &width, &height, &channels, 4);

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);

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

void setImage(uint32_t unit, const Image *image)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, image->handle);
}
