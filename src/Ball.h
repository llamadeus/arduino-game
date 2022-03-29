#pragma once
#include "GameObject.h"

class Ball : public GameObject {
   private:
    float _vx = 40;
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
        _x += _vx * delta;
        _y += _vy * delta;

        if (_vx < 0) {
            _vx -= 2 * delta;
        } else {
            _vx += 2 * delta;
        }

        _vx = constrain(_vx, -80, 80);

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
            _vx = -_vx;
            _vy = _vy * 0.4 + 60 * ratio * 0.6;
        }
    }

    void turnLeft(float ratio) {
        if (_vx > 0) {
            _vx = -_vx;
            _vy = _vy * 0.4 + 60 * ratio * 0.6;
            // _vy = 40 * ratio;
        }
    }

    void reset() {
        _x = _initialX;
        _y = _initialY;
        _vx = _vx < 0 ? -40 : 40;
        _vy = 0;
    }
};
