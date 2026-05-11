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
Pawn::Pawn(char c) : Piece(c, 'P') {}
bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    int dir = (color == 'W') ? -1 : 1;
    int startRow = (color == 'W') ? 6 : 1;
    if (toCol == fromCol && toRow == fromRow + dir && board[toRow][toCol] == nullptr)
        return true;
    if (toCol == fromCol && fromRow == startRow && toRow == fromRow + 2 * dir
        && board[fromRow + dir][fromCol] == nullptr && board[toRow][toCol] == nullptr)
        return true;
    if ((toCol == fromCol + 1 || toCol == fromCol - 1) && toRow == fromRow + dir
        && board[toRow][toCol] != nullptr && isEnemy(board[toRow][toCol]))
        return true;

    return false;
}
Rook::Rook(char c) : Piece(c, 'R') {}
bool Rook::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    if (fromRow != toRow && fromCol != toCol) return false;
    if (!isPathClear(fromRow, fromCol, toRow, toCol, board)) return false;
    if (board[toRow][toCol] != nullptr && !isEnemy(board[toRow][toCol])) return false;
    return true;
}
