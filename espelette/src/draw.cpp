//
// Created by felix on 06/10/2021.
//

#include <draw.h>
#include <glm/gtx/transform.hpp>
#include <image.h>
#include "draw_list.h"

union DrawListStorage
{
    char buf[sizeof(DrawList)] {};
    DrawList drawList;

    constexpr DrawListStorage() noexcept : buf() {};
    ~DrawListStorage() noexcept {};
} drawListStorage;

DrawList& drawList = drawListStorage.drawList;

void drawInit()
{
    new (&drawListStorage.drawList) DrawList();
}

void drawShutdown()
{
    drawListStorage.drawList.~DrawList();
}


void drawSprite(const Image *image, const glm::vec2 &pos)
{
    drawList.sprite(image, pos);
}

void drawSprite(const Image *image, const glm::vec2 &pos, const glm::vec2 &size)
{
    drawList.sprite(image, pos, size);
}


void drawRect(const glm::vec2 &a, const glm::vec2 &b, const glm::u8vec4 &color)
{
    drawList.setImage(nullptr);
    drawList.rect(a, b, color);
}


void setView(float left, float top, float right, float bottom)
{
    drawList.setView(left, top, right, bottom);
}

void DrawList::rect(const glm::vec2 &a, const glm::vec2 &b, const glm::u8vec4& col)
{
    uint32_t baseIndex = vertices.size() - command->baseVertex;

    auto verts = vertices.alloc_back(4);
    verts[0] = { .pos = {a.x, a.y}, .uv = {0, 0}, .col = col };
    verts[1] = { .pos = {a.x, b.y}, .uv = {0, 1}, .col = col };
    verts[2] = { .pos = {b.x, a.y}, .uv = {1, 0}, .col = col };
    verts[3] = { .pos = {b.x, b.y}, .uv = {1, 1}, .col = col };

    auto els = elements.alloc_back(6);
    els[0] = baseIndex + 0;
    els[1] = baseIndex + 1;
    els[2] = baseIndex + 2;
    els[3] = baseIndex + 1;
    els[4] = baseIndex + 2;
    els[5] = baseIndex + 3;

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

