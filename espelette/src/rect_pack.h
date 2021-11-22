//
// Created by felix on 22/11/2021.
//

#pragma once
#include <cstdint>
#include "vec.h"
#include <glm/vec2.hpp>
#include <optional>

struct RectPack
{
    struct Rect
    {
        glm::ivec2 pos;
        glm::ivec2 size;
    };

    struct Node
    {
        Rect rect;
        uint32_t childrenOffset : 31;
        bool filled : 1;
    };

    glm::ivec2 size{};
    Vec<Node> nodes{};

    RectPack();
    explicit RectPack(glm::ivec2 size);

    std::optional<uint32_t> insert(glm::ivec2 rectSize);
};