#include "ip/Display.h"
#include "ip/test.h"
#include "ip/Audio.h"



int main() {
    auto start = std::chrono::steady_clock::now();
    glfwInit();

    auto display = Display();
    auto startupTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start).count();
    std::cout << "Startup complete in " << startupTime << "milliseconds" << std::endl;

    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



