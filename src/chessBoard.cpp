#include <random>
#include <ctime>

#include "chessboard.h"

ChessBoard::ChessBoard(Player playerA, Player playerB)
{
    // Assigning the Players their roles
    std::srand(time(0));
    bool isAFirst = std::rand() % 2 == 0;
    playerA.assignColor(isAFirst ? WHITE : BLACK);
    playerB.assignColor(isAFirst ? BLACK : WHITE);
}