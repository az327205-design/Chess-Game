#include "Piece.h"
#include <cstdlib>
Piece::Piece(char c, char s) : color(c), symbol(s) {}
char Piece::getColor() const { return color; }
char Piece::getSymbol() const { return symbol; }
bool Piece::isEnemy(Piece* other) const {
    if (other == nullptr) return false;
    return other->getColor() != color;
}
bool Piece::isPathClear(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
    int rowStep = 0, colStep = 0;
    if (toRow > fromRow) rowStep = 1;
    else if (toRow < fromRow) rowStep = -1;
    if (toCol > fromCol) colStep = 1;
    else if (toCol < fromCol) colStep = -1;
    int r = fromRow + rowStep;
    int c = fromCol + colStep;
    while (r != toRow || c != toCol) {
        if (board[r][c] != nullptr) return false;
        r += rowStep;
        c += colStep;
    }
    return true;
}
