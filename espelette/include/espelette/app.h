//
// Created by felix on 06/10/2021.
//

#ifndef ESPELETTE_APP_H
#define ESPELETTE_APP_H

class AppInterface
{
public:
    int width {};
    int height {};

    virtual void init(){};
    virtual void update(){};
    virtual void shutdown(){};
};

int run(AppInterface& app);

#endif //ESPELETTE_APP_H

