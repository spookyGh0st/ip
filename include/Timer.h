

#ifndef IP_TIMER_H
#define IP_TIMER_H

#include <chrono>

class Timer {
private:
    using clock = std::chrono::steady_clock;
    using timepoint = std::chrono::time_point<clock>;
    timepoint start = clock::now();
    timepoint current = clock::now();
    unsigned long frames { 0 };
    unsigned long fpsTime { 0 };
public:
    float dt { 0.0f };
    float t { 0.0f };
    long startUpTime();
    void advanceFrame();
};


#endif //IP_TIMER_H
