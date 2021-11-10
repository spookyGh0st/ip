#ifndef IP_DISPLAY_HPP
#define IP_DISPLAY_HPP


#include <ip/Window.hpp>
#include <vector>
#include <chrono>

class Display {
    std::vector<Window> windows{};
    int monitor_x {},monitor_y{};
    std::chrono::time_point<std::chrono::system_clock> startTime {std::chrono::system_clock::now() };
    std::chrono::time_point<std::chrono::system_clock> currentTime {std::chrono::system_clock::now() };
    std::chrono::time_point<std::chrono::system_clock> oldTime { std::chrono::system_clock::now() };
public:
    int width, height;
    Display();
    ~Display();
    void update();
    void createWindow();

    void updatePositions();

    void draw();

    int shouldClose();
};

#endif //IP_DISPLAY_HPP
