#pragma once
#include "Piece.h"

class Board {
private:
private:
    Piece* grid[8][8];
    bool isSquareAttacked(int row, int col, char attackerColor) const;

public:
    Board();
    ~Board();

    void setupBoard();
    void display() const;

    Piece* getPiece(int row, int col) const;
    Piece* (*getGrid())[8] { return grid; }  // returns Piece*(*)[8] — pointer to first row
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isKingAlive(char color) const;
    bool isInCheck(char color);
    bool isCheckmate(char color);
    bool isValidMoveWithCheckProtection(int fromRow, int fromCol, int toRow, int toCol, char color);
};