#include <iostream>
#include "snakeGame.h"
using namespace std;

// milliSecond단위로 코드를 sleep해줌.
void delay (unsigned int msecs) {
	clock_t goal = msecs*CLOCKS_PER_SEC/1000 + clock();
	while ( goal > clock() );
}

SnakeGame::SnakeGame() {
    height = 20; width = 80;

    initWindow();
    drawWall();
    initSnake();
    drawSnake();
}
SnakeGame::~SnakeGame() {
    nodelay(stdscr, false);
    getch();
    endwin();
}
void SnakeGame::initWindow() {
    initscr();
    noecho(); // 유저의 입력이 화면 커서에 나타나지 않게함.
    keypad(stdscr, true); // 방향키의 입력이 가능하게함.
    nodelay(stdscr, true); // getch()가 화면을 멈추지않게함.
    curs_set(0); // 커서 안보이게 함.

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
void SnakeGame::moveSnake() {
    int keyPressed = getch();
    switch (keyPressed) {
    case KEY_UP:
        if (snake.direction != 2) snake.direction = 0;
        break;
    case KEY_RIGHT:
        if (snake.direction != 3) snake.direction = 1;
        break;
    case KEY_DOWN:
        if (snake.direction != 0) snake.direction = 2;
        break;
    case KEY_LEFT:
        if (snake.direction != 1) snake.direction = 3;
        break;
    }

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
        snake.head = Position(snake.head.y + 1, snake.head.x);
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
bool SnakeGame::checkCollision() {
    // head가 벽에 닿았는지 체크
    if (snake.head.y == 0 || snake.head.x == 0 || snake.head.y == height || snake.head.x == width) {
        return true;
    }
    // head가 body와 닿았는지 체크
    for (int i=0; i<snake.tail.size(); i++) {
        if (snake.head.y == snake.tail[i].y && snake.head.x == snake.tail[i].x) {
            return true;
        }
    }
    return false;
}
void SnakeGame::start() {
    while(true) {
        if (checkCollision()) break;
        moveSnake();
        refresh();

        delay(50);
    }
}
