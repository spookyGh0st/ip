

#include <chrono>
#include <iostream>
#include "Timer.h"
#include "log.h"

#define LOG_FPS true


long Timer::startUpTime() {
    current = clock::now();
    auto startupTime = std::chrono::duration_cast<std::chrono::milliseconds>(current-start).count();
    start = current;
    return startupTime;
}

void Timer::advanceFrame() {
    auto now = clock::now();
    auto dtD =std::chrono::duration_cast<std::chrono::milliseconds>(now-current).count();
    dt = float(dtD) / 1000.0f;
    t += dt;
    current = now;
    frames++;
    if (LOG_FPS && ulong(t) > fpsTime){
        logDebug( std::to_string(frames) + " fps");
        fpsTime = ulong(t);
        frames = 0;
    }
}
