#include <iostream>
#include <ctime>
#include <time.h>
#include "snakeGame.h"
using namespace std;

// milliSecond단위로 코드를 sleep해줌.
void delay (unsigned int msecs) {
    clock_t goal = msecs*CLOCKS_PER_SEC/1000 + clock();
    while ( goal > clock() );
}

SnakeGame::SnakeGame():item_start(time(NULL)){
    height = 21; width = 50;
    boardHeight = (height) / 2; boardWidth = 25;
    srand((unsigned int)time(NULL));

    initWindow();
    initWalls();
    drawWalls();
    initSnake();
    drawSnake();
}
SnakeGame::~SnakeGame(){
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
    init_pair(3, 240, 240); // immune 벽 색깔
    init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA); // 유저 색깔
    init_pair(5, COLOR_GREEN, COLOR_GREEN); // GrowthItem 색깔
    init_pair(6, COLOR_RED, COLOR_RED); // PosionItem 색깔
    init_pair(7, COLOR_BLUE, COLOR_BLUE); // gate department 색깔

    scoreBoard = newwin(boardHeight, boardWidth, 1, width+2);
    missionBoard = newwin(boardHeight, boardWidth, 2+boardHeight, width+2);
    box(scoreBoard, 0, 0);
    box(missionBoard, 0 ,0);
}
void SnakeGame::initWalls() {
    for (int i=1; i<=width; i++) {
        if (i == 1 || i == width) walls.push_back(Wall(1, i, true));
        else walls.push_back(Wall(1, i));
    }
    for (int i=1; i<=width; i++) {
        if (i == 1 || i == width) walls.push_back(Wall(height, i, true));
        else walls.push_back(Wall(height, i));
    }
    for (int i=2; i<height; i++) {
        walls.push_back(Wall(i, 1));
    }
    for (int i=2; i<height; i++) {
        walls.push_back(Wall(i, width));
    }
}
void SnakeGame::drawWalls() {
    for (int i=0; i<walls.size(); i++) {
        if (!walls[i].immune) {
            attron(COLOR_PAIR(2));
            move(walls[i].pos.y, walls[i].pos.x);
            addch(' ');
            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(3));
            move(walls[i].pos.y, walls[i].pos.x);
            addch(' ');
            attroff(COLOR_PAIR(3));
        }
    }
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
    attron(COLOR_PAIR(4));
    move(snake.head.y, snake.head.x);
    addch(' ');
    for (int i=0; i<snake.tail.size(); i++) {
        move(snake.tail[i].y, snake.tail[i].x);
        addch(' ');
    }
    attroff(COLOR_PAIR(4));
}
bool SnakeGame::isEatGrowth() {
    vector<Position>::iterator iter;
    for (iter = growthItems.begin(); iter < growthItems.end(); ++iter) {
        if (iter->y == snake.head.y && iter->x == snake.head.x) {
            iter = growthItems.erase(iter);
            return true;
        }
    }
    return false;
}
bool SnakeGame::isEatPoison() {
    vector<Position>::iterator iter;
    for (iter = poisonItems.begin(); iter < poisonItems.end(); ++iter) {
        if (iter->y == snake.head.y && iter->x == snake.head.x) {
            iter = poisonItems.erase(iter);
            return true;
        }
    }
    return false;
}
// 포인터를 리턴한 이유로는 그냥 Wall을 리턴할경우 NULL이 리턴이안되네요 개같은.
Wall* SnakeGame::isOnGate() {
    auto iter = walls.begin();
    for (; iter != walls.end(); iter++) {
        if (iter->gate && iter->pos.y == snake.head.y && iter->pos.x == snake.head.x)
            return iter->destination;
    }
    return NULL;
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
        
    Wall* destination = isOnGate();

    if (destination) {
        // 게이트에 들어갔을때 움직임.
        while (true) {
            snake.head = Position(destination->pos.y, destination->pos.x);
            switch (snake.direction) {
            case 0:
                snake.head = Position(snake.head.y - 1, snake.head.x);
                break;
            case 1:
                snake.head = Position(snake.head.y, snake.head.x + 1);
                break;
            case 2:
                snake.head = Position(snake.head.y + 1, snake.head.x);
                break;
            case 3:
                snake.head = Position(snake.head.y, snake.head.x - 1);
                break;
            }

            /*
                게이트에서 자신의 방향으로 전진해보고, 아니다 싶으면
                direction을 1더하고 4로 나눈뒤 다시 게이트에서 전진해봄.
                이러면 ppt Game Rule에 부합함.
            */
            if (checkCollision()) {
                snake.direction = (snake.direction + 1) % 4;
            } else break; 
        }
    }

    attron(COLOR_PAIR(4));
    move(snake.head.y, snake.head.x);
    addch(' ');
    attroff(COLOR_PAIR(4));

    if (!isEatGrowth() && !destination) {
        attron(COLOR_PAIR(1));
        move(snake.tail[snake.tail.size() - 1].y, snake.tail[snake.tail.size() - 1].x);
        addch(' ');
        snake.tail.pop_back();
        attroff(COLOR_PAIR(1));
    } else {
        snake.length++;
    }
    if (isEatPoison()) {
        attron(COLOR_PAIR(1));
        move(snake.tail[snake.tail.size() - 1].y, snake.tail[snake.tail.size() - 1].x);
        addch(' ');
        snake.tail.pop_back();
        attroff(COLOR_PAIR(1));
        snake.length--;
    }
}
bool SnakeGame::checkCollision() {
    // head가 벽밖으로 나갔는지 체크
    if (snake.head.y < 1 || snake.head.y > height || snake.head.x < 1 || snake.head.x > width)
        return true;

    // head가 벽에 닿았는지 체크
    for (int i=0; i<walls.size(); i++) {
        if (!walls[i].gate && snake.head.y == walls[i].pos.y && snake.head.x == walls[i].pos.x) {
            return true;
        }
    }
    // head가 body와 닿았는지 체크
    for (int i=0; i<snake.tail.size(); i++) {
        if (snake.head.y == snake.tail[i].y && snake.head.x == snake.tail[i].x) {
            return true;
        }
    }
    return false;
}

void SnakeGame::makeItems() {
    //아이템이 나타날 위치 임의로 선정
    bool check = false;
    int Gy, Gx;

    while (!check) {
        check = true;
        Gy = rand() % (height - 2) + 2;
        Gx = rand() % (width - 2) + 2;

        for (int i = 0; i < snake.length; i ++) {
            if (i == 0) {
                if (snake.head.y == Gy && snake.head.x == Gx) {
                    check = false;
                    break;
                }
            }
            else {
                if (snake.tail[i].y == Gy && snake.tail[i].x == Gx) {
                    check = false;
                    break;
                }
            }
        }
    }

    Position temp = Position(Gy, Gx);
    //그 위치에다가 아이템 그려주기
    int growthOrPoison = rand() % 2;     // 0이면 GrowthItem 만들고, 1이면 PoisonItem 만들기
    if (growthOrPoison % 2 == 0) {
        growthItems.push_back(temp);
        attron(COLOR_PAIR(5));
        move(Gy, Gx);
        addch(' ');
        attroff(COLOR_PAIR(5));
    } else {
        poisonItems.push_back(temp);
        attron(COLOR_PAIR(6));
        move(Gy, Gx);
        addch(' ');
        attroff(COLOR_PAIR(6));
    }
    // 더해야될것 : 몇초 지나면 사라지게.
}

void SnakeGame::removeItems(){

    vector<Position>::iterator iter;
    for (iter = growthItems.begin(); iter < growthItems.end(); ++iter) { // GrowthItem에 있는 Position정보들 모두 배경색으로 칠하기.
        attron(COLOR_PAIR(1));
        move(iter->y, iter->x);
        addch(' ');
        attroff(COLOR_PAIR(1));
    }
    growthItems.clear(); // GrowthItem에 있는 Position 정보 초기화 

    for (iter = poisonItems.begin(); iter < poisonItems.end(); ++iter) { // PoisonItem에 있는 Position정보들 모두 배경색으로 칠하기.
        attron(COLOR_PAIR(1));
        move(iter->y, iter->x);
        addch(' ');
        attroff(COLOR_PAIR(1));
    }
    poisonItems.clear(); // PoisonItem에 있는 Position 정보 초기화 
}

void SnakeGame::makeGate() {
    int idx = rand() % walls.size();
    while (walls[idx].immune)
        idx = rand() % walls.size();

    int destinationIdx = rand() % walls.size();
    while (walls[destinationIdx].immune || idx == destinationIdx)
        destinationIdx = rand() % walls.size();

    walls[idx].gate = true;
    walls[destinationIdx].gate = true;
    walls[idx].destination = &walls[destinationIdx];
    walls[destinationIdx].destination = &walls[idx];

    attron(COLOR_PAIR(7));
    move(walls[idx].pos.y, walls[idx].pos.x);
    addch(' ');
    move(walls[destinationIdx].pos.y, walls[destinationIdx].pos.x);
    addch(' ');
    attroff(COLOR_PAIR(7));
}
void SnakeGame::drawScoreBoard() {
}
void SnakeGame::start() {
    makeGate();

    while(true) {
        if (snake.length < 3) break;
        if (checkCollision()) break;

        item_curr = time(NULL) - item_start; // 타이머 측정 
        if (growthItems.size() + poisonItems.size() < 3){
            makeItems();
            item_start = time(NULL); // 타이머 초기화

        }
        if (item_curr > 5){ // item 생성시간이 5초를 초과하면 아이템 재생성  
            removeItems();
        }
        moveSnake();
        drawScoreBoard();
        refresh();
        wrefresh(scoreBoard);
        wrefresh(missionBoard);

        delay(100);
    }
}
