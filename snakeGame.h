#include <ncurses.h>
#include <vector>
#include "struct.h"
#include <time.h>
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

class SnakeGame {
private:
    int height, width;
    int boardHeight, boardWidth;
    int blockBoardHeight, blockBoardWidth;
    int levelBoardHeight, levelBoardWidth;
    int score, level;
    std::vector<Position> growthItems;
    std::vector<Position> poisonItems;
    std::vector<Wall> walls;
    Snake snake;
    time_t item_start, item_curr;
    WINDOW *scoreBoard;
    WINDOW *missionBoard;
    WINDOW *blockBoard;
    WINDOW *levelBoard;
    WINDOW *gameOverWindow;
    WINDOW *victoryWindow;
    // window생성과 각종 필요한 설정을 해줌.
    void initWindow();
    // wall을 초기화해줌.
    void initWalls();
    // 최초 wall을 그려줌.
    void drawWalls();
    // snake를 초기화해줌.
    void initSnake();
    // 최초 snake를 그려줌.
    void drawSnake();
    // snake 움직임을 처리해줌.
    void moveSnake();
    // 충돌했는지 아닌지 판별해줌.
    // 충돌했다면 return true, 아니라면 return false.
    bool checkCollision();
    // Item 만들기.
    void makeItems();
    // Item 지우기.
    void removeItems();
    // gate 만들기.
    void makeGate();
    // GrowthItem 먹었는지 아닌지 판별하기.
    bool isEatGrowth();
    // PoisonItem 먹었는지 아닌지 판별하기.
    bool isEatPoison();
    // gate 위에 있는지 아닌지 판별하기.
    Wall* isOnGate();
    // Board 초기화.
    void initBoard();
    // scoreBoard 새로고침.
    void drawBoard();
    // mission을 Clear했는지.
    bool isClear();
    // 다음 맵으로 이동.
    void nextMap();
    // Game Board 지우기.
    void clearGameBoard();
    void clearDrawBoard();
    
public:
    SnakeGame();
    ~SnakeGame();
    // 게임을 시작하고 유지해줌.
    void start();
};

#endif
