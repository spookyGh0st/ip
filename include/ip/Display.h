#ifndef IP_DISPLAY_H
#define IP_DISPLAY_H


#include <ip/Window.h>
#include <vector>
#include <chrono>
#include "Audio.h"

class Display {
    AudioFile audioVisualizationFile;
    AudioFile audioPlaybackFile;
    AudioPlayback audioPlayback;
    Window window;
    ip::Scene scene;

    int monitor_x {},monitor_y{};
    std::chrono::time_point<std::chrono::system_clock> startTime {std::chrono::system_clock::now() };
    std::chrono::time_point<std::chrono::system_clock> currentTime {std::chrono::system_clock::now() };
    std::chrono::time_point<std::chrono::system_clock> oldTime { std::chrono::system_clock::now() };

public:
    int width, height;
    Display();
    ~Display();

    void update();
    int shouldClose();

};

#endif //IP_DISPLAY_H
