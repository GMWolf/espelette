//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_APP_H
#define ESPELETTE_APP_H

#include <glm/vec2.hpp>

struct AppInterface
{
    void (*init)(){};
    void (*shutdown)(){};
    void (*update)(){};
};

int run(const AppInterface& app);

glm::vec2 windowSize();

#endif //ESPELETTE_APP_H

