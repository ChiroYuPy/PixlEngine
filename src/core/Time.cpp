//
// Created by ChiroYuki on 24/07/2025.
//

#include "core/Time.h"

void Time::start() {
    m_startTime = Clock::now();
    m_lastFrameTime = m_startTime;
}

void Time::update() {
    TimePoint now = Clock::now();
    std::chrono::duration<float> frameDuration = now - m_lastFrameTime;
    m_deltaTime = frameDuration.count();
    m_lastFrameTime = now;
}

float Time::getDeltaTime() const {
    return m_deltaTime;
}

float Time::getElapsedTime() const {
    std::chrono::duration<float> elapsed = Clock::now() - m_startTime;
    return elapsed.count();
}