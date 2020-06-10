#include "struct.h"
#include <cstddef>
#include <cstdlib>
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

Wall::Wall() {
    pos = Position();
    immune = false;
    gate = false;
    destination = NULL;
}
Wall::Wall(int y, int x, bool immune) {
    pos = Position(y, x);
    this->immune = immune;
    gate = false;
    destination = NULL;
}