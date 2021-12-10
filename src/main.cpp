#include "ip/Display.h"
#include "ip/test.h"

int main() {
    glfwInit();
    testTape();
    auto display { Display() };

    // render loop
    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



