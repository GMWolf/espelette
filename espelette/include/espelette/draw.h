//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_DRAW_H
#define ESPELETTE_DRAW_H

#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "vec.h"

struct Image;

struct Vertex
{
    glm::vec2 pos;
    glm::vec2 uv;
    glm::u8vec4 col;
};

struct DrawCommand
{
    uint32_t count;
    uint32_t indexOffset;
    uint32_t baseVertex;
    glm::mat4 projMat;
    uint32_t imageHandle;
};

using element_t = uint32_t;

struct DrawList
{
    Vec<Vertex> vertices;
    Vec<element_t> elements;
    Vec<DrawCommand> commands;
    DrawCommand* command {};

    DrawList();

    void rect(const glm::vec2& a, const glm::vec2& b, const glm::u8vec4& col);
    void sprite(const Image* image, const glm::vec2& pos);
    void sprite(const Image* image, const glm::vec2& pos, const glm::vec2& size);
    void setView(float left, float top, float right, float bottom);
    void setImage(const Image* image);

    void clear();

    void newCommand();
    void flushCommand();
};

void submit(DrawList& drawList);

#endif //ESPELETTE_DRAW_H
