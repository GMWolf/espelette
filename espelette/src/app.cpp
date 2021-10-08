//
// Created by felix on 06/10/2021.
//

#include "app.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "draw.h"
#include <stb_image.h>

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

    setWindowIcon(window, "logo.png");

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    drawInit();

    app.init();

    while(!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, width, height);

        app.width = width;
        app.height = height;

        app.update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.shutdown();

    drawShutdown();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

