//
// Created by felix on 06/10/2021.
//

#include "draw.h"
#include <glm/gtx/transform.hpp>


void DrawList::rect(const glm::vec2 &a, const glm::vec2 &b, const glm::u8vec4& col)
{
    uint32_t baseIndex = vertices.size() - command->baseVertex;

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

    command->count += 6;
}

void DrawList::clear()
{
    vertices.clear();
    elements.clear();
    commands.clear();
    newCommand();
}

void DrawList::setView(float left, float top, float right, float bottom)
{
    glm::mat4 mat = glm::ortho(left, right, bottom, top);

    if (mat != command->projMat)
    {
        flushCommand();
        command->projMat = mat;
    }
}

void DrawList::setImage(const Image *image)
{
    uint32_t handle = image ? image->handle : 0;
    if (handle != command->imageHandle)
    {
        flushCommand();
        command->imageHandle = image ? image->handle : 0;
    }
}


void DrawList::newCommand()
{
    commands.push_back(DrawCommand{
            .count = 0,
            .indexOffset = static_cast<uint32_t>( elements.byte_size() ),
            .baseVertex = static_cast<uint32_t>( vertices.size() ),
            .projMat = glm::ortho(0, 1, 0, 1),
            .imageHandle = 0,
    });
    command = static_cast<DrawCommand*>(commands.getBack());
}

void DrawList::flushCommand()
{
    if (command->count > 0)
    {
        commands.push_back(DrawCommand{
                .count = 0,
                .indexOffset = static_cast<uint32_t>( elements.byte_size() ),
                .baseVertex = static_cast<uint32_t>( vertices.size() ),
                .projMat = command->projMat,
                .imageHandle = command->imageHandle,
        });
        command = static_cast<DrawCommand*>(commands.getBack());
    }
}

DrawList::DrawList()
{
    newCommand();
}

void DrawList::sprite(const Image *image, const glm::vec2 &pos, const glm::vec2& size)
{
    setImage(image);
    rect(pos, pos + size, {255, 255, 255, 255});
}

void DrawList::sprite(const Image *image, const glm::vec2& pos)
{
    sprite(image, pos, {image->width, image->height});
}

