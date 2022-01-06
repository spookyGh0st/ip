#include "test.h"
#include "Audio.h"
#include "Window.h"
#include "Scene.h"
#include "Timer.h"

#define audioPath "/home/user/Music/2 Mello - Sounds Of Tokyo-To Future/2 Mello - Sounds Of Tokyo-To Future - 13 Poison Jam (Part II).ogg"

int main() {

    auto start = std::chrono::system_clock::now();
    Timer t {};
    glfwInit();

    AudioSync sync { audioPath };
    Window window { };
    ip::Scene scene { &sync };
    scene.setResolution(window.width,window.height);

    logInfo("Startup complete in " + std::to_string(t.startUpTime()) + "milliseconds");

    sync.audioPlayback.play();

    while(!window.shouldClose()) {
        t.advanceFrame();
        window.processInput();
        scene.update(t.dt, t.t);
        glClearColor(0.0f,1.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        scene.render(t.dt,t.t);
        glfwPollEvents();
        window.swapBuffers();
    }

    return 0;
}



