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
    drawList.view(0, 0, width, height);

    setImage(0, image);
    drawList.rect({10, 10}, {150, 150}, {255, 255, 255, 255});
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