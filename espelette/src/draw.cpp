//
// Created by felix on 06/10/2021.
//

#include "draw.h"

#include <glad/gl.h>

struct DrawBackendData
{
    bool initialized {};
    GLuint vertexBuffer {};
    GLuint indexBuffer {};
    GLuint vertexArray {};
    GLuint shader {};
    GLint textureLocation;
};

static DrawBackendData drawData {};

void submit(DrawList& drawList)
{
    glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.indexBuffer);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(drawList.vertices.byte_size()), drawList.vertices.data(), GL_STREAM_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(drawList.elements.byte_size()), drawList.elements.data(), GL_STREAM_DRAW);

    glBindVertexArray(drawData.vertexArray);

    glUseProgram(drawData.shader);
    glUniform1i(drawData.textureLocation, 0);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(drawList.elements.size()), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawList::rect(const glm::vec2 &a, const glm::vec2 &b, const glm::u8vec4& col)
{
    uint32_t baseIndex = vertices.size();
    vertices.push_back({ .pos = {a.x, a.y}, .uv = {0, 0}, .col = col });
    vertices.push_back({ .pos = {a.x, b.y}, .uv = {0, 1}, .col = col });
    vertices.push_back({ .pos = {b.x, a.y}, .uv = {1, 0}, .col = col });
    vertices.push_back({ .pos = {b.x, b.y}, .uv = {1, 1}, .col = col });

    elements.push_back(baseIndex + 0);
    elements.push_back(baseIndex + 1);
    elements.push_back(baseIndex + 2);
    elements.push_back(baseIndex + 1);
    elements.push_back(baseIndex + 2);
    elements.push_back(baseIndex + 3);
}

void DrawList::clear()
{
    vertices.clear();
    elements.clear();
}

static const char* vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec2 uv;\n"
        "layout (location = 2) in vec4 color;\n"
        "out vec2 fragUV;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "   fragUV = uv;\n"
        "   fragColor = color;\n"
        "   gl_Position = vec4( position, 0.0, 1.0 );\n"
        "}\n";

static const char* fragmentShader =
        "#version 330 core\n"
        "in vec2 fragUV;\n"
        "in vec4 fragColor;\n"
        "uniform sampler2D tex;\n"
        "out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "   outColor = fragColor * texture(tex, fragUV);\n"
        "}\n";

static GLuint createShaderProgram()
{
    GLuint vshd = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshd, 1, &vertexShader, nullptr);
    glCompileShader(vshd);

    GLuint fshd = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshd, 1, &fragmentShader, nullptr);
    glCompileShader(fshd);

    GLuint program = glCreateProgram();
    glAttachShader(program, vshd);
    glAttachShader(program, fshd);
    glLinkProgram(program);

    glDetachShader(program, vshd);
    glDetachShader(program, fshd);
    glDeleteShader(vshd);
    glDeleteShader(fshd);

    return program;
}

void drawInit()
{
    if (!drawData.initialized)
    {
        glGenBuffers(1, &drawData.vertexBuffer);
        glGenBuffers(1, &drawData.indexBuffer);
        glGenVertexArrays(1, &drawData.vertexArray);

        glBindVertexArray(drawData.vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.indexBuffer);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        drawData.shader = createShaderProgram();
        drawData.textureLocation = glGetUniformLocation(drawData.shader, "tex");

        drawData.initialized = true;
    }
}


void drawShutdown()
{
    if (drawData.initialized)
    {
        glDeleteBuffers(1, &drawData.vertexBuffer);
        glDeleteBuffers(1, &drawData.indexBuffer);
        glDeleteVertexArrays(1, &drawData.vertexArray);

        glDeleteProgram(drawData.shader);

        drawData.initialized = false;
    }
}