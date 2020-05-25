#include <vector>
#ifndef SNAKE_H
#define SNAKE_H

struct Position {
    int y, x;
    Position();
    Position(int col, int row);
};

class Snake {
public:
    int length, direction;
    Position head;
    std::vector<Position> tail;

    Snake();
    Snake(std::vector<Position> body);
    // head와 body가 겹치는지 알려줌.
    bool isTwisted();
};

#endif