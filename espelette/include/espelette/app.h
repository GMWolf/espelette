//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_APP_H
#define ESPELETTE_APP_H

#include <glm/vec2.hpp>

enum class AppFlow
{
    CONTINUE,
    CLOSE,
};

struct AppInterface
{
    glm::ivec2 windowSize{};
    void (*init)(){};
    void (*shutdown)(){};
    AppFlow (*update)(){};
};

int run(const AppInterface& app);

glm::vec2 windowSize();

#endif //ESPELETTE_APP_H

