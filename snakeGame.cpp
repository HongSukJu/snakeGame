#include "snakeGame.h"
using namespace std;

SnakeGame::SnakeGame() {
    width = 80; height = 20;

    initWindow();
    drawWall();
}
SnakeGame::~SnakeGame() {
    endwin();
}
void SnakeGame::initWindow() {
    initscr();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
}
void SnakeGame::drawWall() {
    attron(COLOR_PAIR(1));

    for (int i=0; i<width; i++) {
        move(0, i);
        addch(' ');
    }
    for (int i=0; i<width; i++) {
        move(height-1, i);
        addch(' ');
    }
    for (int i=0; i<height; i++) {
        move(i, 0);
        addch(' ');
    }
    for (int i=0; i<height; i++) {
        move(i, width-1);
        addch(' ');
    }
}
void SnakeGame::start() {
    refresh();
    getch();
}