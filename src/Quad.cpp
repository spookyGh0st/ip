

#include "ip/Scene.h"
#include <ip/Tape.h>
#include <glad/glad.h>
#include <filesystem>
#include "ip/Quad.h"

Quad::Quad() {
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);

    const GLfloat vertices[] = {
            -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &quad_vbo);
    // todo error checking
}

Quad::~Quad() {
    glDeleteVertexArrays(1, &quad_vao);
}

void Quad::render() const {
    glBindVertexArray(quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}