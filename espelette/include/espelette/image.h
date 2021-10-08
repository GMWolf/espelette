//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_IMAGE_H
#define ESPELETTE_IMAGE_H

#include <cstdint>

struct Image
{
    uint16_t width;
    uint16_t height;
    uint32_t handle;
};

Image* loadImage(const char* path);
void freeImage(Image* image);

#endif //ESPELETTE_IMAGE_H
