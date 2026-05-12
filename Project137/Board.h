#pragma once
#include "Piece.h"

class Board {
private:
    Piece* grid[8][8];

public:
    Board();
    ~Board();

    void setupBoard();
    void display() const;
    Piece* getPiece(int row, int col) const;
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

};