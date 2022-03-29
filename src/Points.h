#pragma once
#include "GameObject.h"

const int OFFSET_FROM_CENTER = 3;

class Points : public GameObject {
   private:
    int _player1Score = 0;
    int _player2Score = 0;

   public:
    void update(float delta) {
    }

    void draw(U8G2* display) {
        String player1 = String(_player1Score);
        String player2 = String(_player2Score);

        display->drawStr(display->getWidth() / 2 - player1.length() * 6 - OFFSET_FROM_CENTER, 8, player1.c_str());
        display->drawStr(display->getWidth() / 2 + OFFSET_FROM_CENTER, 8, player2.c_str());
    }

    void incrementPlayer1() {
        _player1Score += 1;
    }

    void incrementPlayer2() {
        _player2Score += 1;
    }
};
