//
// Created by felix on 06/10/2021.
//

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/gl.h>

Image *loadImage(const char *path)
{
    ImageData imageData = loadImageData(path);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageData.width, imageData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data);
    glGenerateMipmap(GL_TEXTURE_2D);



    auto* image = new Image {
        .width = static_cast<uint16_t>(imageData.width),
        .height = static_cast<uint16_t>(imageData.height),
        .handle = static_cast<uint16_t>(texture)
    };

    freeImageData(imageData);

    return image;
}

void freeImage(Image *image)
{
    glDeleteTextures(1, &image->handle);
    delete image;
}

ImageData loadImageData(const char *path)
{
    ImageData image{};
    int channels;
    image.data = stbi_load(path, &image.width, &image.height, &channels, 4);
    return image;
}

void freeImageData(ImageData &imageData)
{
    stbi_image_free(imageData.data);
    imageData.data = nullptr;
}
