#pragma once
#include "Board.h"
#include <string>
using namespace std;

class Game {
private:
    Board board;
    char currentTurn;
    void parsePosition(const string& pos, int& row, int& col);
    bool isValidInput(const string& pos);
    char askPromotion();                     // asks player which piece to promote to

public:
    Game();
    void start();
};
