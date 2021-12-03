#include <filesystem>
#include <glad/glad.h>
#include <ip/Tape.h>
#include "ip/Scene.h"

using namespace ip;

Scene::Scene() :
    shader(ShaderProgram( std::filesystem::path("/home/user/uni/sem7/ip/assets/shaders/vert.glsl"), std::filesystem::path("/home/user/uni/sem7/ip/assets/shaders/frag.glsl"))),
    quad(Quad()),
    tape(createTapeFromExprString("sqrt(x^2+y^2+z^2)+1)"))
    {
    shader.bindTexArr();
}

Scene::~Scene() = default;

void Scene::update(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t) {

}

void Scene::render(std::chrono::duration<long, std::ratio<1, 1000000000>> dt, std::chrono::time_point<std::chrono::system_clock> t) {
    shader.use();
    quad.render();
}

void Scene::onKey(int key, int scancode, int action, int mode) {

}

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
