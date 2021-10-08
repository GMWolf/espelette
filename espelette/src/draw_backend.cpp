//
// Created by felix on 07/10/2021.
//

#include "draw.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

struct DrawBackendData
{
    bool initialized {};
    GLuint vertexBuffer {};
    GLuint indexBuffer {};
    GLuint vertexArray {};
    GLuint shader {};
    GLint textureLocation {};
    GLint matLocation {};
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

    for(const DrawCommand& command : drawList.commands)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, command.imageHandle);

        glUniformMatrix4fv(drawData.matLocation, 1, false, glm::value_ptr(command.projMat));

        glDrawElementsBaseVertex(GL_TRIANGLES, static_cast<GLsizei>(command.count), GL_UNSIGNED_INT,
                                 reinterpret_cast<void*>(command.indexOffset), static_cast<GLint>(command.baseVertex));
    }


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static const char* vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec2 uv;\n"
        "layout (location = 2) in vec4 color;\n"
        "uniform mat4 projMat;\n"
        "out vec2 fragUV;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "   fragUV = uv;\n"
        "   fragColor = color;\n"
        "   gl_Position = projMat * vec4( position, 0.0, 1.0 );\n"
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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        drawData.shader = createShaderProgram();
        drawData.textureLocation = glGetUniformLocation(drawData.shader, "tex");
        drawData.matLocation = glGetUniformLocation(drawData.shader, "projMat");

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