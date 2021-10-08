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

    drawList.sprite(image, {10, 10});
    drawList.sprite(logoImage, {170, 10});
    drawList.sprite(logoImage, {320, 10}, glm::vec2(logoImage->width, logoImage->height) * 1.25f);

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