#include <filesystem>
#include "glad.h"
#include "Tape.h"
#include "Scene.h"

using namespace ip;

Scene::Scene(AudioSync *audioSync) :
        shader(ShaderProgram( std::filesystem::path("/home/user/uni/sem7/ip/assets/shaders/vert.glsl"), std::filesystem::path("/home/user/uni/sem7/ip/assets/shaders/frag.glsl"))),
        quad(Quad()),
        tape(createTapeFromExprString("min(y,sqrt(x*x+(y-1)*(y-1)+(z-6)*(z-6))-1)")),
        audioS(audioSync)
{
    shader.use();
    shader.bindTapeBuffer("tapeSampler", (uint8_t *) (tape.instructions.data()), "tapeSize", tape.instructions.size(), 0);
    shader.bindRamBuffer("ramSampler", tape.constants.data(), "ramSize", tape.constants.size(), 1);

    glEnable(GL_FRAMEBUFFER_SRGB);
}

Scene::~Scene() = default;

// todo better sync, fix delay, maybe predict or what?
void Scene::update(float dt, float t) {
    camera.update(dt,t);
    auto view = camera.getViewMatrix();
    shader.bindMat4("view", view);
    shader.bindVec3("cameraPos", camera.position);

    auto ad = audioS->read(dt);
    shader.bindFloat(keyPulseL,ad.leftTotal);
    shader.bindFloat(keyPulseR,ad.rightTotal);
    for (int i = 0; i < NFFT/2; ++i) {
        auto name = "histogram["+ std::to_string(i)+"]";
        shader.bindFloat(name,ad.spectogram[i]);
    }
}

void Scene::render(float dt, float t) {
    shader.use();
    woodTexture.bind(shader);
    duckTexture.bind(shader);
    quad.render();
}

void Scene::setResolution(float width, float height) {
    shader.use();
    std::string keyResolution { "iResolution" };
    shader.bindVec2(keyResolution, width, height);
}

void Scene::onKey(int key, int scancode, int action, int mode) {

}

