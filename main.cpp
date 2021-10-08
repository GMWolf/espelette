#include <espelette.h>

class App : public AppInterface
{
    DrawList drawList {};
    Image* image {};
    Image* logoImage {};

public:
    void init() override;
    void update() override;
    void shutdown() override;
};

void App::init()
{
    image = loadImage("test.png");
    logoImage = loadImage("logo.png");
}

void App::update()
{
    drawList.setView(0, 0, width, height);

    drawList.setImage(image);
    drawList.rect({10, 10}, {150, 150}, {255, 255, 255, 255});

    drawList.setImage(logoImage);
    drawList.rect({160, 10}, {310, 150}, {255, 255, 255, 255});
    drawList.rect({320, 10}, {470, 150}, {255, 255, 255, 255});

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