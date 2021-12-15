#include <iostream>
#include "ip/Display.h"
#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

using namespace std::chrono;

Display::Display(): window(Window()), scene(ip::Scene()){
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPos(monitor,&monitor_x,&monitor_y);
    const GLFWvidmode *modes = glfwGetVideoMode(monitor);
    width = modes->width;
    height = modes->height;
    window.setSize(float(width)/2,float(height)/2);
    window.setPosition(float(monitor_x) + float(width)/2 , float(monitor_y) + float(height) / 2);
    scene.setResolution(width/2,height/2);
}

Display::~Display() {
    glfwTerminate();
}

void Display::update() {
    currentTime = std::chrono::system_clock::now();
    auto deltaTime = currentTime - oldTime;

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
