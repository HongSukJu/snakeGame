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
    int shortcutBoardHeight, shortcutBoardWidth;
    int score,level;
    std::vector<Position> growthItems;
    std::vector<Position> poisonItems;
    std::vector<Wall> walls,maps,map3,map4,stage;
    Snake snake;
    time_t item_start, item_curr;
    WINDOW *scoreBoard;
    WINDOW *missionBoard;
    WINDOW *blockBoard;
    WINDOW *shortcutBoard;
    WINDOW *gameOverWindow;
    //stage가 바뀔 떄 마다 다시 시작 기릿.
    void restart();
    // window생성과 각종 필요한 설정을 해줌.
    void initWindow();
    // wall을 초기화해줌.
    void initWalls();
    // level에 따라 맵을 그려준다.
    void initMaps();
    // 그린 맵으로 바꿔준다.
    void changeMaps();
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
    //mission 기릿.
    void mission();
    
public:
    SnakeGame();
    ~SnakeGame();
    // 게임을 시작하고 유지해줌.
    void start();
};

#endif
