#include <vector>
#ifndef SNAKE_H
#define SNAKE_H

struct Position {
    int y, x;
    Position();
    Position(int col, int row);
};

struct Snake {
    int length;
    int direction; // direction의 기준은 시계방향, 즉 0이 위, 1이 오른쪽, 2는 아래, 3은 왼쪽.
    Position head;
    std::vector<Position> tail;

    Snake();
    Snake(std::vector<Position> body);
};

#endif