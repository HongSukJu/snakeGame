#include "snakeGame.h"
using namespace std;

SnakeGame::SnakeGame() {
    height = 20; width = 80;

    initWindow();
    drawWall();
    initSnake();
    drawSnake();
}
SnakeGame::~SnakeGame() {
    getch();
    endwin();
}
void SnakeGame::initWindow() {
    initscr();
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // 배경 색깔
    init_pair(2, COLOR_WHITE, COLOR_WHITE); // 벽 색깔
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA); // 유저 색깔
}
void SnakeGame::drawWall() {
    attron(COLOR_PAIR(2));
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
    attroff(COLOR_PAIR(2));
}
void SnakeGame::initSnake() {
    vector<Position> body;
    for (int i=0; i<3; i++) {
        Position temp = Position(10, 40+i);
        body.push_back(temp);
    }
    snake = Snake(body);
}
void SnakeGame::drawSnake() {
    attron(COLOR_PAIR(3));
    move(snake.head.y, snake.head.x);
    addch(' ');
    for (int i=0; i<snake.tail.size(); i++) {
        move(snake.tail[i].y, snake.tail[i].x);
        addch(' ');
    }
    attroff(COLOR_PAIR(3));
}
void SnakeGame::moveSnake() {\
    attron(COLOR_PAIR(1));
    move(snake.tail[snake.length - 2].y, snake.tail[snake.length - 2].x);
    addch(' ');
    snake.tail.pop_back();
    attroff(COLOR_PAIR(1));

    switch (snake.direction) {
    case 0:
        snake.tail.insert(snake.tail.begin(), snake.head);
        snake.head = Position(snake.head.y - 1, snake.head.x);
        break;
    case 1:
        snake.tail.insert(snake.tail.begin(), snake.head);
        snake.head = Position(snake.head.y, snake.head.x + 1);
        break;
    case 2:
        snake.tail.insert(snake.tail.begin(), snake.head);
        snake.head = Position(snake.head.y - 1, snake.head.x);
        break;
    case 3:
        snake.tail.insert(snake.tail.begin(), snake.head);
        snake.head = Position(snake.head.y, snake.head.x - 1);
        break;
    }

    attron(COLOR_PAIR(3));
    move(snake.head.y, snake.head.x);
    addch(' ');
    attroff(COLOR_PAIR(3));
}
void SnakeGame::start() {
    while(true) {
        moveSnake();
        refresh();

        getch();
    }
}
