//
// Created by felix on 09/10/2021.
//

#ifndef ESPELETTE_INPUT_STATE_H
#define ESPELETTE_INPUT_STATE_H

#include <glm/vec2.hpp>
#include <input.h>

struct InputState
{
    glm::vec2 mousePos;

    uint32_t keyPressedFrame[static_cast<int>(KEY::COUNT)]{0};
    uint32_t keyReleasedFrame[static_cast<int>(KEY::COUNT)]{0};

    int frame = 1;
};

extern InputState inputState;

#endif //ESPELETTE_INPUT_STATE_H
