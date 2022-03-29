#pragma once
#include "GameObject.h"

const int BAR_WIDTH = 2;
const int BAR_HEIGHT = 12;
const int BAR_SPEED = 50;

class PlayerBar : public GameObject {
   protected:
    int _buttonUp;
    int _buttonDown;

   public:
    PlayerBar(int x, int buttonUp, int buttonDown) {
        _x = x;
        _y = 48 / 2;

        _buttonUp = buttonUp;
        _buttonDown = buttonDown;
    }

    void update(float delta) {
        if (digitalRead(_buttonUp) == LOW) {
            _y -= BAR_SPEED * delta;
        }

        if (digitalRead(_buttonDown) == LOW) {
            _y += BAR_SPEED * delta;
        }

        _y = constrain(_y, BAR_HEIGHT / 2, 48 - BAR_HEIGHT / 2);
    }

    void draw(U8G2* display) {
        display->drawBox(_x - BAR_WIDTH / 2, _y - BAR_HEIGHT / 2, BAR_WIDTH, BAR_HEIGHT);
    }

    float getTop() {
        return _y - BAR_HEIGHT / 2;
    }

    float getBottom() {
        return _y + BAR_HEIGHT / 2;
    }

    int getHeight() {
        return BAR_HEIGHT;
    }

    void reset() {
        _y = 48 / 2;
    }
};
