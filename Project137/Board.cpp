#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = nullptr;
    setupBoard();
}

Board::~Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
}

void Board::setupBoard() {
    // Black back row
    grid[0][0] = new Rook('B');
    grid[0][1] = new Knight('B');
    grid[0][2] = new Bishop('B');
    grid[0][3] = new Queen('B');
    grid[0][4] = new King('B');
    grid[0][5] = new Bishop('B');
    grid[0][6] = new Knight('B');
    grid[0][7] = new Rook('B');
    for (int j = 0; j < 8; j++)
        grid[1][j] = new Pawn('B');

    // White back row
    grid[7][0] = new Rook('W');
    grid[7][1] = new Knight('W');
    grid[7][2] = new Bishop('W');
    grid[7][3] = new Queen('W');
    grid[7][4] = new King('W');
    grid[7][5] = new Bishop('W');
    grid[7][6] = new Knight('W');
    grid[7][7] = new Rook('W');
    for (int j = 0; j < 8; j++)
        grid[6][j] = new Pawn('W');
}

void Board::display() const {
    const string RESET = "\033[0m";
    const string WHITE_PIECE = "\033[1;97m";      // Bold bright white
    const string BLACK_PIECE = "\033[1;91m";      // Bold bright red
    const string LIGHT_SQ = "\033[48;5;250m";  // Light grey square
    const string DARK_SQ = "\033[48;5;236m";  // Dark grey square
    const string LABEL_COL = "\033[1;93m";       // Bold yellow labels

    cout << "\n" << LABEL_COL << "    a   b   c   d   e   f   g   h" << RESET << "\n";
    cout << LABEL_COL << "  +---+---+---+---+---+---+---+---+" << RESET << "\n";

    for (int i = 0; i < 8; i++) {
        cout << LABEL_COL << (8 - i) << " |" << RESET;

        for (int j = 0; j < 8; j++) {
            bool isLight = (i + j) % 2 == 0;
            string sq = isLight ? LIGHT_SQ : DARK_SQ;

            if (grid[i][j] == nullptr) {
                cout << sq << "   " << RESET;
            }
            else {
                char sym = grid[i][j]->getSymbol();
                char col = grid[i][j]->getColor();
                string pc = (col == 'W') ? WHITE_PIECE : BLACK_PIECE;
                cout << sq << pc << " " << sym << " " << RESET;
            }
            cout << LABEL_COL << "|" << RESET;
        }

        cout << LABEL_COL << " " << (8 - i) << RESET << "\n";
        cout << LABEL_COL << "  +---+---+---+---+---+---+---+---+" << RESET << "\n";
    }

    cout << LABEL_COL << "    a   b   c   d   e   f   g   h" << RESET << "\n\n";
    cout << LIGHT_SQ << WHITE_PIECE << " White " << RESET
        << "  "
        << DARK_SQ << BLACK_PIECE << " Black " << RESET << "\n";
    cout << "\033[1;37m  K=King Q=Queen R=Rook B=Bishop N=Knight P=Pawn\033[0m\n\n";
}

Piece* Board::getPiece(int row, int col) const {
    return grid[row][col];
}

bool Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7) return false;
    if (toRow < 0 || toRow  > 7 || toCol < 0 || toCol  > 7) return false;

    Piece* piece = grid[fromRow][fromCol];
    if (piece == nullptr) return false;
    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, grid)) return false;

    delete grid[toRow][toCol];
    grid[toRow][toCol] = piece;
    grid[fromRow][fromCol] = nullptr;
    return true;
}

bool Board::isKingAlive(char color) const {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr &&
                grid[i][j]->getColor() == color &&
                grid[i][j]->getSymbol() == 'K')
                return true;
    return false;
}

bool Board::isInCheck(char color) {
    // Find king
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr &&
                grid[i][j]->getColor() == color &&
                grid[i][j]->getSymbol() == 'K') {
                kingRow = i; kingCol = j;
            }
    if (kingRow == -1) return false;

    char enemy = (color == 'W') ? 'B' : 'W';
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr && grid[i][j]->getColor() == enemy)
                if (grid[i][j]->isValidMove(i, j, kingRow, kingCol, grid))
                    return true;
    return false;
}

bool Board::isCheckmate(char color) {
    // Not checkmate if not even in check
    if (!isInCheck(color)) return false;

    // Try every possible move for every piece of this color
    // If any move results in the king no longer being in check, it's NOT checkmate
    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Piece* piece = grid[fromRow][fromCol];
            if (piece == nullptr || piece->getColor() != color) continue;

            for (int toRow = 0; toRow < 8; toRow++) {
                for (int toCol = 0; toCol < 8; toCol++) {
                    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, grid)) continue;

                    // Simulate the move
                    Piece* captured = grid[toRow][toCol];
                    grid[toRow][toCol] = piece;
                    grid[fromRow][fromCol] = nullptr;

                    bool stillInCheck = isInCheck(color);

                    // Undo the move
                    grid[fromRow][fromCol] = piece;
                    grid[toRow][toCol] = captured;

                    if (!stillInCheck)
                        return false; // Found a move that escapes check
                }
            }
        }
    }

    // No escape found — it's checkmate
    return true;

}

bool Board::isValidMoveWithCheckProtection(int fromRow, int fromCol, int toRow, int toCol, char color) {
    Piece* piece = grid[fromRow][fromCol];
    if (piece == nullptr) return false;
    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, grid)) return false;

    // Simulate the move
    Piece* captured = grid[toRow][toCol];
    grid[toRow][toCol] = piece;
    grid[fromRow][fromCol] = nullptr;

    bool leavesKingInCheck = isInCheck(color);

    // Undo the move
    grid[fromRow][fromCol] = piece;
    grid[toRow][toCol] = captured;

    return !leavesKingInCheck;
}