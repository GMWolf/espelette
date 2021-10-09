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

void update()
{
    if (keyDown(KEY::A))
        pos.x -= 1;

    if (keyDown(KEY::D))
        pos.x += 1;

    if (keyDown(KEY::W))
        pos.y -= 1;

    if (keyDown(KEY::S))
        pos.y += 1;

    setView(0, 0, windowSize().x,  windowSize().y);

    drawSprite(logoImage, {170, 10});
    drawSprite(logoImage, {320, 10}, glm::vec2(logoImage->width, logoImage->height) * 1.25f);

    drawSprite(image, pos);
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