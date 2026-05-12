#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : currentTurn('W') {}

void Game::parsePosition(const string& pos, int& row, int& col) {
    col = pos[0] - 'a';
    row = 8 - (pos[1] - '0');
}

bool Game::isValidInput(const string& pos) {
    if (pos.size() != 2) return false;
    if (pos[0] < 'a' || pos[0] > 'h') return false;
    if (pos[1] < '1' || pos[1] > '8') return false;
    return true;
}

void Game::start() {
    cout << "==========================================\n";
    cout << "        CHESS GAME  -  OOP in C++\n";
    cout << "    FAST NUCES Faisalabad-Chiniot Campus\n";
    cout << "==========================================\n";
    cout << "  How to play:\n";
    cout << "    Enter moves as:  <from> <to>\n";
    cout << "    Example:         e2 e4\n";
    cout << "  Type 'quit' to exit.\n";
    cout << "==========================================\n";

    string from, to;

    while (true) {
        board.display();

        // Checkmate detection — checked BEFORE asking for input
        if (board.isCheckmate(currentTurn)) {
            char winner = (currentTurn == 'W') ? 'B' : 'W';
            cout << "==========================================\n";
            cout << "  CHECKMATE! " << (winner == 'W' ? "White" : "Black") << " wins!\n";
            cout << "==========================================\n";
            break;
        }

        // Check warning
        if (board.isInCheck(currentTurn)) {
            cout << "  !! " << (currentTurn == 'W' ? "WHITE" : "BLACK") << " IS IN CHECK !!\n\n";
        }

        cout << (currentTurn == 'W' ? "White" : "Black") << "'s turn.\n";
        cout << "Enter move: ";
        cin >> from;

        if (from == "quit") {
            cout << "Game ended by player. Goodbye!\n";
            break;
        }

        cin >> to;

        if (!isValidInput(from) || !isValidInput(to)) {
            cout << "  [!] Invalid input! Use format like: e2 e4\n\n";
            continue;
        }

        int fromRow, fromCol, toRow, toCol;
        parsePosition(from, fromRow, fromCol);
        parsePosition(to, toRow, toCol);

        Piece* piece = board.getPiece(fromRow, fromCol);

        if (piece == nullptr) {
            cout << "  [!] No piece at " << from << "!\n\n";
            continue;
        }
        if (piece->getColor() != currentTurn) {
            cout << "  [!] That is not your piece!\n\n";
            continue;
        }

        // First check if the piece can even make this move by its own rules
        if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, board.getGrid())) {
            cout << "  [!] Invalid move for this piece!\n\n";
            continue;
        }

        // Then check if the move would leave own king in check
        if (!board.isValidMoveWithCheckProtection(fromRow, fromCol, toRow, toCol, currentTurn)) {
            cout << "  [!] Invalid move! This would leave your King in check.\n\n";
            continue;
        }

        board.movePiece(fromRow, fromCol, toRow, toCol);

        // Switch turns
        currentTurn = (currentTurn == 'W') ? 'B' : 'W';
    }
}