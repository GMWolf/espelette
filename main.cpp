#include <espelette.h>

Image* image {};
Image* logoImage {};
glm::vec2 pos;

void init()
{
    image = loadImage("test.png");
    logoImage = loadImage("logo.png");
    pos = {10, 10};
}

void shutdown()
{
    freeImage(image);
    freeImage(logoImage);
}

void updatePos()
{
    if (keyDown(KEY::A) || keyDown(KEY::LEFT))
        pos.x -= 1;
    if (keyDown(KEY::D) || keyDown(KEY::RIGHT))
        pos.x += 1;
    if (keyDown(KEY::W) || keyDown(KEY::UP))
        pos.y -= 1;
    if (keyDown(KEY::S) || keyDown(KEY::DOWN))
        pos.y += 1;
}

AppFlow update()
{
    if (keyPressed(KEY::ESCAPE))
        return AppFlow::CLOSE;

    updatePos();

    setView(0, 0, windowSize().x,  windowSize().y);

    drawSprite(logoImage, {170, 10});
    drawSprite(logoImage, {320, 10}, glm::vec2(logoImage->width, logoImage->height) * 1.25f);

    drawSprite(image, pos);

    return AppFlow::CONTINUE;
}

int main()
{
    run({
        .windowSize = {1280, 720},
        .init = init,
        .shutdown = shutdown,
        .update = update,
    });
}