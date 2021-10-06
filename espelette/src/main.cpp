#include "app.h"
#include "image.h"
#include "draw.h"

class App : public AppInterface
{
    DrawList drawList {};
    Image* image {};

public:
    void init() override;
    void update() override;
    void shutdown() override;
};

void App::init()
{
    image = loadImage("test.png");
}

void App::update()
{
    setImage(0, image);
    drawList.rect({-0.5, -0.5}, {0.5, 0.5}, {255, 255, 255, 255});
    submit(drawList);
    drawList.clear();
}

void App::shutdown()
{
    freeImage(image);
}

int main()
{
    App app{};
    run(app);
}