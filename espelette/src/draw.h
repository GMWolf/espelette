//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_DRAW_H
#define ESPELETTE_DRAW_H

#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "vec.h"

struct Vertex
{
    glm::vec2 pos;
    glm::vec2 uv;
    glm::u8vec4 col;
};

struct DrawList
{
    Vec<Vertex> vertices;
    Vec<uint32_t> elements;
    void rect(const glm::vec2& a, const glm::vec2& b, const glm::u8vec4& col);

    void clear();
};

void drawInit();
void drawShutdown();

void submit(DrawList& drawList);

#endif //ESPELETTE_DRAW_H
