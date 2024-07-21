#ifndef PROJECT_4_UTILS_H
#define PROJECT_4_UTILS_H

#include <iostream>
#include <cmath>
#include <chrono>

double getCurrentTimeInSeconds() {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    long duration = value.count();
    return duration / 1000.0;
}

// Function to get the sine value based on the current time
double getSineWave(double time, double period) {
    double frequency = 1.0 / period;
    return std::sin(2.0 * M_PI * frequency * time);
}

// Function to get sine with 180 degrees in 3 seconds
double getSin180In3Seconds() {
    double currentTime = getCurrentTimeInSeconds();
    return getSineWave(currentTime, 18.0); // 18 seconds for a full 360 degrees cycle
}

#endif //PROJECT_4_UTILS_H
