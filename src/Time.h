#pragma once
#include <Arduino.h>

class Time {
   private:
    unsigned long _lastFrame = 0;

    bool _enableFPS = false;
    int _fpsTimer = 0;
    int _fpsCounter = 0;

    void tickFPS(int delta) {
        _fpsTimer += delta;
        _fpsCounter += 1;

        if (_fpsTimer >= 1000) {
            Serial.println(String("fps: ") + _fpsCounter);

            _fpsTimer -= 1000;
            _fpsCounter = 0;
        }
    }

   public:
    float update() {
        unsigned long current = millis();
        int delta = current - _lastFrame;

        _lastFrame = current;

        if (_enableFPS) {
            tickFPS(delta);
        }

        return (float)delta / 1000;
    }

    void enableFPS() {
        _enableFPS = true;
    }
};
