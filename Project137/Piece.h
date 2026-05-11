#pragma once
#include <vector>
#include <string>
using namespace std;
class Piece {
protected:
    char color; // 'W' or 'B'
    char symbol;

public:
    Piece(char c, char s);
    virtual ~Piece() {}

    char getColor() const;
    char getSymbol() const;

    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) = 0;

    bool isEnemy(Piece* other) const;
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const;
};

