//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_DRAW_H
#define ESPELETTE_DRAW_H

#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Image;

void drawSprite(const Image* image, const glm::vec2& pos);
void drawSprite(const Image* image, const glm::vec2& pos, const glm::vec2& size);
void setView(float left, float top, float right, float bottom);

void drawRect(const glm::vec2& a, const glm::vec2& b, const glm::u8vec4& color);


#endif //ESPELETTE_DRAW_H
