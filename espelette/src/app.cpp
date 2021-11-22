//
// Created by felix on 06/10/2021.
//

#include <app.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <stb_image.h>

#include "input_state.h"
#include "draw_backend.h"
#include "font.h"

struct AppGlobals
{
    glm::vec2 windowSize;
};

static AppGlobals appGlobals;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(action)
    {
        case GLFW_PRESS:
            inputState.keyPressedFrame[key] = inputState.frame;
            break;
        case GLFW_RELEASE:
            inputState.keyReleasedFrame[key] = inputState.frame;
            break;
        default:
            break;
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch(action)
    {
        case GLFW_PRESS:
            inputState.mousePressedFrame[button] = inputState.frame;
            break;
        case GLFW_RELEASE:
            inputState.mouseReleasedFrame[button] = inputState.frame;
            break;
        default:
            break;
    }
}

static void setWindowIcon(GLFWwindow* window, const char* file)
{
    GLFWimage logoImage;
    logoImage.pixels = stbi_load(file, &logoImage.width, &logoImage.height, nullptr, 4);
    if (logoImage.width > 0)
    {
        glfwSetWindowIcon(window, 1, &logoImage);
    }
    stbi_image_free(logoImage.pixels);
}

int run(const AppInterface& app)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize glfw");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    const char* title = app.title ? app.title : "Espelette";

    GLFWwindow* window = glfwCreateWindow(app.windowSize.x, app.windowSize.y, title, nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Failed to create window");
        glfwTerminate();
        return 1;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    const char* iconPath = app.icon ? app.icon : "logo.png";
    setWindowIcon(window, iconPath);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    drawInit();
    drawBackendInit();
    initFontCache();

    app.init();

    auto fnt = createFont("KaushanScript-Regular.ttf");
    cacheCodePoint(fnt, 2);
    cacheCodePoint(fnt, 1);


    while(!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        appGlobals.windowSize = {width, height};

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        inputState.mousePos = glm::vec2(mouseX, mouseY);

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, width, height);

        AppFlow flow = app.update();

        drawList.setImage(getCacheTexture());
        drawList.rect({0,0}, {512, 512}, {255,255,255,255});

        submit(drawList);
        drawList.clear();

        if (flow == AppFlow::CLOSE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        glfwSwapBuffers(window);
        inputState.frame++;
        glfwPollEvents();
    }

    app.shutdown();

    drawBackendShutdown();
    drawShutdown();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

glm::vec2 windowSize()
{
    return appGlobals.windowSize;
}

