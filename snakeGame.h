#include <ncurses.h>
#include <vector>
#include "snake.h"
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

class SnakeGame {
private:
    int height, width;
    std::vector<Position> growthItem;
    std::vector<Position> immuneWall;
    Snake snake;

    // window생성과 각종 필요한 설정을 해줌.
    void initWindow();
    // 가장자리 벽을 그려줌.
    void drawWall();
    // snake를 초기화해줌.
    void initSnake();
    // 최초 snake를 그려줌.
    void drawSnake();
    // snake 움직임을 처리해줌.
    void moveSnake();
    // 충돌했는지 아닌지 판별해줌.
    // 충돌했다면 return true, 아니라면 return false.
    bool checkCollision();
    // GrowthItem 만들기.
    void makeGrowthItem();
    // GrowthItem 먹었는지 아닌지 판별하기.
    bool isEat();
    
public:
    SnakeGame();
    ~SnakeGame();
    // 게임을 시작하고 유지해줌.
    void start();
};

#endif
