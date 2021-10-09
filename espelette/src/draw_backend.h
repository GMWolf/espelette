//
// Created by felix on 09/10/2021.
//

#ifndef ESPELETTE_DRAW_BACKEND_H
#define ESPELETTE_DRAW_BACKEND_H

#include "draw_list.h"

void submit(DrawList& drawList);

void drawBackendInit();
void drawBackendShutdown();


#endif //ESPELETTE_DRAW_BACKEND_H
