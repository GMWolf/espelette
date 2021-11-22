//
// Created by felix on 22/11/2021.
//

#include "rect_pack.h"
#include <optional>
#include <glm/vec4.hpp>


RectPack::RectPack(glm::ivec2 size) : size(size)
{
    nodes.push_back(Node{
        .rect = {
                .pos = {0, 0},
                .size = size
        },
        .childrenOffset = 0,
        .filled = false
    });
}

RectPack::RectPack() : RectPack(glm::ivec2(0)){
}


static glm::ivec4 splitRect(glm::ivec4 rect, uint32_t splitCoord, bool vertical, int index)
{
    if (vertical)
    {
        if (index == 0)
        {
            return glm::ivec4 {
                    rect.x, rect.y,
                    rect.z, splitCoord,
            };
        }
        else
        {
            return glm::ivec4 {
                rect.x, rect.y + splitCoord,
                rect.z, rect.w - splitCoord
            };
        }
    }
    else
    {
        if (index == 0)
        {
            return glm::ivec4 {
                    rect.x, rect.y,
                    splitCoord, rect.w
            };
        }
        else
        {
            return glm::ivec4 {
                    rect.x + splitCoord, rect.y,
                    rect.z - splitCoord, rect.w
            };
        }
    }
}

static std::optional<uint32_t> insert(RectPack& pack, uint32_t nodeId, glm::ivec2 rectSize)
{
    if (pack.nodes[nodeId].childrenOffset > 0)
    {
        auto result = ::insert(pack, nodeId + pack.nodes[nodeId].childrenOffset, rectSize);
        if (result) return *result;

        result = ::insert(pack, nodeId + pack.nodes[nodeId].childrenOffset + 1, rectSize);
        return result;
    }
    else
    {
        RectPack::Rect rect = pack.nodes[nodeId].rect;

        if (pack.nodes[nodeId].filled)
        {
            return std::nullopt;
        }

        if (rectSize.x > rect.size.x || rectSize.y > rect.size.y)
        {
            return std::nullopt;
        }

        if (rectSize.x == rect.size.x && rectSize.y == rect.size.y)
        {
            pack.nodes[nodeId].filled = true;
            return nodeId;
        }

        //Create children
        pack.nodes[nodeId].childrenOffset = pack.nodes.size() - nodeId;
        auto* children = pack.nodes.alloc_back(2);
        children[0].filled = false;
        children[0].childrenOffset = 0;
        children[1].filled = false;
        children[1].childrenOffset = 0;

        int dw = rect.size.x - rectSize.x;
        int dh = rect.size.y - rectSize.y;

        if (dw > dh)
        {
            children[0].rect = {
                    rect.pos,
                    {rectSize.x, rect.size.y}
            };
            children[1].rect = {
                    {rect.pos.x + rectSize.x, rect.pos.y},
                    {rect.size.x - rectSize.x, rectSize.y}
            };
        }
        else
        {
            children[0].rect = {
                    rect.pos,
                    {rect.size.x, rectSize.y}
            };
            children[1].rect = {
                    {rect.pos.x, rect.pos.y + rectSize.y},
                    {rect.size.x, rect.size.y - rectSize.y}
            };
        }

        return insert(pack, nodeId + pack.nodes[nodeId].childrenOffset, rectSize);
    }
}

std::optional<uint32_t> RectPack::insert(glm::ivec2 rectSize)
{
    return ::insert(*this, 0, rectSize);
}

