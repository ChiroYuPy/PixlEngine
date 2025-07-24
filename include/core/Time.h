//
// Created by ChiroYuki on 24/07/2025.
//

#ifndef PIXLENGINE_TIME_H
#define PIXLENGINE_TIME_H

#include <chrono>

class Time {
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    void start();
    void update();

    float getDeltaTime() const;
    float getElapsedTime() const;

private:
    TimePoint m_startTime;
    TimePoint m_lastFrameTime;
    float m_deltaTime = 0.0f;
};

#endif //PIXLENGINE_TIME_H
