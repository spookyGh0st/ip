#include <iostream>
#include "ip/Display.h"
#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

using namespace std::chrono;

Display::Display() {
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPos(monitor,&monitor_x,&monitor_y);
    const GLFWvidmode *modes = glfwGetVideoMode(monitor);
    width = modes->width;
    height = modes->height;
}

Display::~Display() {
    glfwTerminate();
}

void Display::update() {
    currentTime = std::chrono::system_clock::now();
    auto deltaTime = currentTime - oldTime;
    // updatePositions();
    draw();
}

void Display::createWindow() {
    windows.emplace_back();
    windows.back().setSize(height/2.0);
    windows.back().setPosition(monitor_x+(width)/2.0,monitor_y + height /2.0);
}

void Display::updatePositions() {
    for (int i = 0; i < windows.size(); i++){
        auto ang { (double(i) / double(windows.size())) * 2.0 * E_PI };
        auto to = (currentTime - startTime).count();
        ang += double(to)/1000000000;
        auto radius { std::min(width,height)/4};
        auto x { (width/2.0) + sin(ang) * radius }; //todo change 100
        auto y { (height/2.0) + cos(ang) * radius };
        windows[i].setPosition(monitor_x +x,monitor_y + y);

        auto minSize = double(width)/16.0;
        windows[i].setSize(0.5*minSize*cos(ang)+minSize);
    }
}

void Display::draw() {
    for (auto & window : windows){
        window.processInput();
        window.draw();
    }
}

int Display::shouldClose() {
    for (auto & window : windows){
        if(window.shouldClose())
            return window.shouldClose();
    }
    return GLFW_FALSE;
}
