#include "snake.h"
using namespace std;

Position::Position() {
    y = 0;
    x = 0;
}
Position::Position(int col, int row) {
    y = col;
    x = row;
}

Snake::Snake() {
    length = 0;
    direction = 0;
    head = Position();
}
Snake::Snake(vector<Position> body) {
    head = body[0];
    tail = vector<Position>(body.begin() + 1, body.end());
    length = body.size();
    direction = 3;
};
bool Snake::isTwisted() {
    for (int i=0; i<tail.size(); i++) {
        if (head.y == tail[i].y && head.x == tail[i].x) {
            return true;
        }
    }
    return false;
}