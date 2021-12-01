#include <ip/Tape.h>
#include "ip/Display.h"

int main() {
    glfwInit();
    auto display { Display() };

    // render loop
    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



