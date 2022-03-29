#include <Arduino.h>
#include <TaskScheduler.h>
#include <U8g2lib.h>

#include "Ball.h"
#include "GameObject.h"
#include "PlayerBar.h"
#include "Points.h"
#include "Time.h"

const int BUTTON_A = 6;
const int BUTTON_B = 7;
const int BUTTON_C = 8;
const int BUTTON_D = 9;

U8G2_PCD8544_84X48_1_4W_HW_SPI display(U8G2_R0, 4, 5, 3);

// Game engine
void update();
void render();

// Run update and render every X ms
Scheduler ts;
Task updateTask(1000 / 100, TASK_FOREVER, &update, &ts, true);
Task renderTask(1000 / 60, TASK_FOREVER, &render, &ts, true);

// Game objects
Time time;
PlayerBar player1(2, BUTTON_A, BUTTON_B);
PlayerBar player2(84 - 2, BUTTON_C, BUTTON_D);
Ball ball(display.getWidth() / 2, display.getHeight() / 2);
Points points;
GameObject* objects[] = {&player1, &player2, &ball, &points};

void setup(void) {
    Serial.begin(9600);

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    // Initialize display
    display.begin();
    display.setContrast(150);
    display.setFont(u8g2_font_6x10_mn);

    // Start fps timer
    time.enableFPS();
}

void loop(void) {
    // Run scheduler
    ts.execute();
}

void update() {
    float delta = time.update();

    for (auto object : objects) {
        object->update(delta);
    }

    // Game logic
    float ballTop = ball.getY() - 1;
    float ballBottom = ball.getY() + 1;

    if (ball.getX() < 4) {
        if (ballBottom > player1.getTop() && ballTop < player1.getBottom()) {
            float collisionY = ball.getY() - player1.getY();
            float ratio = collisionY / (player1.getHeight() / 2);

            ball.turnRight(ratio);
        }

        if (ball.getX() <= 0) {
            // Player 1 lost
            points.incrementPlayer2();
            ball.reset();
            player1.reset();
            player2.reset();
        }
    } else if (ball.getX() >= 84 - 3) {
        if (ballBottom > player2.getTop() && ballTop < player2.getBottom()) {
            float collisionY = ball.getY() - player2.getY();
            float ratio = collisionY / (player2.getHeight() / 2);

            ball.turnLeft(ratio);
        }

        if (ball.getX() >= 84) {
            // Player 2 lost
            points.incrementPlayer1();
            ball.reset();
            player1.reset();
            player2.reset();
        }
    }
}

void render() {
    display.firstPage();
    do {
        // Draw game objects
        for (auto object : objects) {
            object->draw(&display);
        }
    } while (display.nextPage());
}
