#include "ip/Display.h"

using namespace std::chrono;
#define audioPath "/home/user/Music/2 Mello - Sounds Of Tokyo-To Future/2 Mello - Sounds Of Tokyo-To Future - 13 Poison Jam (Part II).ogg"
#define tmpPath "/home/user/Music/2 Mello - Sounds Of Tokyo-To Future/2 Mello - Sounds Of Tokyo-To Future - 14 Chainsaw Funk.ogg"

Display::Display()
: audioSync(audioPath), window(Window()), scene(&audioSync)
{
    // graphic setup
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPos(monitor,&monitor_x,&monitor_y);
    const GLFWvidmode *modes = glfwGetVideoMode(monitor);
    width = modes->width;
    height = modes->height;
    window.setSize(float(width)/2,float(height)/2);
    window.setPosition(float(monitor_x) + float(width)/2 , float(monitor_y) + float(height) / 2);
    scene.setResolution(width/2,height/2);

    currentTime = std::chrono::system_clock::now();
    audioSync.audioPlayback.play();
}

Display::~Display() {
    glfwTerminate();
}

void Display::update() {
    currentTime = std::chrono::system_clock::now();
    auto deltaTime = currentTime - oldTime;
    auto time = startTime - currentTime;
    oldTime = currentTime;

    window.processInput();
    scene.update(deltaTime, currentTime); // todo fix time
    glClearColor(0.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    scene.render(deltaTime,currentTime); // todo fix time
    glfwPollEvents();
    window.swapBuffers();
}


int Display::shouldClose() {
    return window.shouldClose();
}
