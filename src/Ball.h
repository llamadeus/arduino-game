#pragma once
#include "GameObject.h"

const float ENTRY_ANGLE_FACTOR = 0.4;
const float BAR_MANIPULATOR = 1 - ENTRY_ANGLE_FACTOR;
const float BAR_MANIPULATOR_MAX_ANGLE = 70;

class Ball : public GameObject {
   private:
    float _velociRAPTOR = 40;

    float _vx = 1;
    float _vy = 0;

    int _initialX;
    int _initialY;

   public:
    Ball(int x, int y) {
        _x = x;
        _y = y;
        _initialX = x;
        _initialY = y;
    }

    void update(float delta) {
        _x += _velociRAPTOR * _vx * delta;
        _y += _velociRAPTOR * _vy * delta;

        _velociRAPTOR += 2 * delta;

        _velociRAPTOR = constrain(_velociRAPTOR, -80, 80);

        if (_y <= 0 && _vy < 0) {
            _y = 0;
            _vy = -_vy;
        }

        if (_y >= 48 && _vy > 0) {
            _y = 48;
            _vy = -_vy;
        }
    }

    void draw(U8G2* display) {
        display->drawBox(_x - 1, _y - 1, 2, 2);
    }

    void turnRight(float ratio) {
        if (_vx < 0) {
            float currentAngle = atan2(_vy, _vx) * RAD_TO_DEG;
            float schwuggel = currentAngle >= 90 ? 180 - currentAngle : -180 - currentAngle;
            float rad =
                (schwuggel * ENTRY_ANGLE_FACTOR + BAR_MANIPULATOR_MAX_ANGLE * ratio * BAR_MANIPULATOR) * DEG_TO_RAD;

            _vx = cos(rad);
            _vy = sin(rad);
        }
    }

    void turnLeft(float ratio) {
        if (_vx > 0) {
            float currentAngle = atan2(_vy, _vx) * RAD_TO_DEG;
            float rad =
                -1 * (180 + (currentAngle * ENTRY_ANGLE_FACTOR + BAR_MANIPULATOR_MAX_ANGLE * ratio * BAR_MANIPULATOR)) *
                DEG_TO_RAD;

            _vx = cos(rad);
            _vy = sin(rad);
        }
    }

    void reset() {
        _x = _initialX;
        _y = _initialY;
        _velociRAPTOR = 40;
        _vx = _vx < 0 ? -1 : 1;
        _vy = 0;
    }
};
