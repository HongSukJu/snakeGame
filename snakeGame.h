#include <ncurses.h>
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

class SnakeGame {
private:
    int width, height;

    void initWindow();
    void drawWall();
public:
    SnakeGame();
    ~SnakeGame();
    void start();
};

#endif