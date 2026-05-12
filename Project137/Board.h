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


    bool isKingAlive(char color) const;
    bool isInCheck(char color);
    bool isCheckmate(char color);
    bool isValidMoveWithCheckProtection(int fromRow, int fromCol, int toRow, int toCol, char color);

};