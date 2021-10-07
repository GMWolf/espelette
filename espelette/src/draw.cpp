//
// Created by felix on 06/10/2021.
//

#include "draw.h"
#include <glm/gtx/transform.hpp>

void DrawList::rect(const glm::vec2 &a, const glm::vec2 &b, const glm::u8vec4& col)
{
    uint32_t baseIndex = vertices.size();
    vertices.push_back({ .pos = {a.x, a.y}, .uv = {0, 0}, .col = col });
    vertices.push_back({ .pos = {a.x, b.y}, .uv = {0, 1}, .col = col });
    vertices.push_back({ .pos = {b.x, a.y}, .uv = {1, 0}, .col = col });
    vertices.push_back({ .pos = {b.x, b.y}, .uv = {1, 1}, .col = col });

    elements.push_back(baseIndex + 0);
    elements.push_back(baseIndex + 1);
    elements.push_back(baseIndex + 2);
    elements.push_back(baseIndex + 1);
    elements.push_back(baseIndex + 2);
    elements.push_back(baseIndex + 3);
}

void DrawList::clear()
{
    vertices.clear();
    elements.clear();
}

void DrawList::view(float left, float top, float right, float bottom)
{
    projMat = glm::ortho(left, right, bottom, top);
}
