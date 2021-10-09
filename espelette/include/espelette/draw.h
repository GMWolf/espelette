//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_DRAW_H
#define ESPELETTE_DRAW_H

#include <cstdint>
#include <glm/vec2.hpp>

struct Image;

void drawSprite(const Image* image, const glm::vec2& pos);
void drawSprite(const Image* image, const glm::vec2& pos, const glm::vec2& size);
void setView(float left, float top, float right, float bottom);

#endif //ESPELETTE_DRAW_H
