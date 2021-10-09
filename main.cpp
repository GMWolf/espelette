#include <espelette.h>

class App : public AppInterface
{
    DrawList drawList {};
    Image* image {};
    Image* logoImage {};

    glm::vec2 pos;

public:
    void init() override;
    void update() override;
    void shutdown() override;
};

void App::init()
{
    image = loadImage("test.png");
    logoImage = loadImage("logo.png");
    pos = {10, 10};
}

void App::update()
{

    if (keyDown(KEY::A))
        pos.x -= 1;

    if (keyDown(KEY::D))
        pos.x += 1;

    if (keyDown(KEY::W))
        pos.y -= 1;

    if (keyDown(KEY::S))
        pos.y += 1;

    drawList.setView(0, 0, width, height);

    drawList.sprite(image, pos);
    drawList.sprite(logoImage, {170, 10});
    drawList.sprite(logoImage, {320, 10}, glm::vec2(logoImage->width, logoImage->height) * 1.25f);

    submit(drawList);
    drawList.clear();
}

void App::shutdown()
{
    freeImage(image);
    freeImage(logoImage);
}

int main()
{
    App app{};
    run(app);
}