#include "Game.h"
#include <iostream>
#include <stdexcept>
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

        if (board.isCheckmate(currentTurn)) {
            char winner = (currentTurn == 'W') ? 'B' : 'W';
            cout << "==========================================\n";
            cout << "  CHECKMATE! " << (winner == 'W' ? "White" : "Black") << " wins!\n";
            cout << "==========================================\n";
            break;
        }

        if (board.isInCheck(currentTurn))
            cout << "  !! " << (currentTurn == 'W' ? "WHITE" : "BLACK") << " IS IN CHECK !!\n\n";

        cout << (currentTurn == 'W' ? "White" : "Black") << "'s turn.\n";
        cout << "Enter move: ";
        cin >> from;

        if (from == "quit") {
            cout << "Game ended by player. Goodbye!\n";
            break;
        }

        cin >> to;

        try {
            if (!isValidInput(from) || !isValidInput(to))
                throw invalid_argument("Invalid input! Use format like: e2 e4");

            int fromRow, fromCol, toRow, toCol;
            parsePosition(from, fromRow, fromCol);
            parsePosition(to, toRow, toCol);

            Piece* piece = board.getPiece(fromRow, fromCol);

            if (piece == nullptr)
                throw runtime_error("No piece at " + from + "!");

            if (piece->getColor() != currentTurn)
                throw runtime_error("That is not your piece!");

            if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, board.getGrid()))
                throw runtime_error("Invalid move for this piece!");

            if (!board.isValidMoveWithCheckProtection(fromRow, fromCol, toRow, toCol, currentTurn))
                throw runtime_error("This move would leave your King in check!");

            board.movePiece(fromRow, fromCol, toRow, toCol);
            currentTurn = (currentTurn == 'W') ? 'B' : 'W';
        }
        catch (const invalid_argument& e) {
            cout << "  [!] " << e.what() << "\n\n";
        }
        catch (const runtime_error& e) {
            cout << "  [!] " << e.what() << "\n\n";
        }
    }
}