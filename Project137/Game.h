#pragma once
#include "Board.h"
#include <string>
using namespace std;

class Game {
private:
    Board board;
    char currentTurn; // 'W' or 'B'

    void parsePosition(const string& pos, int& row, int& col);
    bool isValidInput(const string& pos);

public:
    Game();
    void start();
};
