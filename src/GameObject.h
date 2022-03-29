#pragma once
#include <U8g2lib.h>

class GameObject {
   protected:
    float _x = 0;
    float _y = 0;

   public:
    void setPosition(float x, float y) {
        _x = x;
        _y = y;
    }

    float getX() {
        return _x;
    }

    float getY() {
        return _y;
    }

    virtual void update(float delta);
    virtual void draw(U8G2* display);
};
