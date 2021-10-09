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

int run(AppInterface& app)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize glfw");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Espelette", nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Failed to create window");
        glfwTerminate();
        return 1;
    }

    glfwSetKeyCallback(window, keyCallback);

    setWindowIcon(window, "logo.png");

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    drawInit();
    drawBackendInit();

    app.init();

    while(!glfwWindowShouldClose(window))
    {
        inputState.frame++;

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, width, height);

        app.width = width;
        app.height = height;

        app.update();

        submit(drawList);
        drawList.clear();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.shutdown();

    drawBackendShutdown();
    drawShutdown();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

