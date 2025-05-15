#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "mylib.h"
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
const int MAX_LENGTH = WIDTH * HEIGHT;
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int fruitX, fruitY;
int length;
int direction; // 0: up, 1: right, 2: down, 3: left

void initialize() {
    length = 1;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    direction = 1;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void draw() {
    system("cls"); // Clear screen
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";
            if (i == snakeY[0] && j == snakeX[0])
                cout << "O"; // Head of snake
            else if (i == fruitY && j == fruitX)
                cout << "X"; // Fruit
            else {
                bool print = false;
                for (int k = 1; k < length; k++) {
                    if (i == snakeY[k] && j == snakeX[k]) {
                        cout << "o"; // Body of snake
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
}

void input() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 'w' || key == 'W')
            direction = 0;
        else if (key == 'd' || key == 'D')
            direction = 1;
        else if (key == 's' || key == 'S')
            direction = 2;
        else if (key == 'a' || key == 'A')
            direction = 3;
    }
}

void logic() {
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;
    snakeX[0] = snakeX[0] + (direction == 1 ? 1 : direction == 3 ? -1 : 0);
    snakeY[0] = snakeY[0] + (direction == 2 ? 1 : direction == 0 ? -1 : 0);

    if (snakeX[0] >= WIDTH)
        snakeX[0] = 0;
    else if (snakeX[0] < 0)
        snakeX[0] = WIDTH - 1;
    if (snakeY[0] >= HEIGHT)
        snakeY[0] = 0;
    else if (snakeY[0] < 0)
        snakeY[0] = HEIGHT - 1;

    for (int i = 1; i < length; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        length++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    initialize();
    while (true) {
        draw();
        input();
        logic();

        Sleep(100);
    }
    return 0;
}
