//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_IMAGE_H
#define ESPELETTE_IMAGE_H

#include <cstdint>
#include "draw.h"


struct Image
{
    uint16_t width;
    uint16_t height;
    uint32_t handle;
};

enum class ImageFiltering
{
    Nearest,
    Linear,
};

Image* createImage(uint16_t width, uint16_t height, ImageFiltering filtering, size_t channels, void* data);
Image* loadImage(const char* path, ImageFiltering filtering = ImageFiltering::Linear);
void freeImage(Image* image);

#endif //ESPELETTE_IMAGE_H
