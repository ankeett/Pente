#include "Board.h"


using namespace std;

void Board::printBoard() {
        // Print column labels (1 - 19)
        std::cout << "  ";
        for (int col = 0; col < 19; col++) {
            std::cout << col + 1 << ' ';
        }
        std::cout << "\n";

        // Print the board with row labels (A - S)
        for (int row = 0; row < 19; row++) {
            std::cout << static_cast<char>('A' + row) << ' '; // Print row label
            for (int col = 0; col < 19; col++) {
                if (board[row][col] == 0) {
                    std::cout << ". "; // Empty cell
                }
                else if (board[row][col] == 1) {
                    std::cout << "X "; // Player 1's stone
                }
                else {
                    std::cout << "O "; // Player 2's stone
                }
            }
            std::cout << "\n";
        }

}