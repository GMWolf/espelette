//
// Created by felix on 09/10/2021.
//

#include <input.h>

#include "input_state.h"

InputState inputState {};

bool keyDown(KEY key)
{
    return inputState.keyReleasedFrame[static_cast<int>(key)] < inputState.keyPressedFrame[static_cast<int>(key)];
}

bool keyUp(KEY key)
{
    return !keyDown(key);
}

bool keyPressed(KEY key)
{
    return inputState.keyPressedFrame[static_cast<int>(key)] == inputState.frame;
}

bool keyReleased(KEY key)
{
    return inputState.keyReleasedFrame[static_cast<int>(key)] == inputState.frame;
}

glm::vec2 mousePos()
{
    return inputState.mousePos;
}

bool mouseDown(MOUSE_BUTTON button)
{
    return inputState.mouseReleasedFrame[static_cast<int>(button)] < inputState.keyReleasedFrame[static_cast<int>(button)];
}

bool mouseUp(MOUSE_BUTTON button)
{
    return !mouseDown(button);
}

bool mousePressed(MOUSE_BUTTON button)
{
    return inputState.mousePressedFrame[static_cast<int>(button)] == inputState.frame;
}

bool mouseReleased(MOUSE_BUTTON button)
{
    return inputState.mouseReleasedFrame[static_cast<int>(button)] == inputState.frame;
}