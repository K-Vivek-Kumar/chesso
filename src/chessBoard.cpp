#include <random>
#include <ctime>

#include "chessboard.h"

ChessBoard::ChessBoard(Player &playerA, Player &playerB)
{
    // Assigning the Players their roles
    std::srand(time(0));
    bool isFirst = std::rand() % 2 == 0;
    playerA.assignColor(isFirst ? WHITE : BLACK);
    playerB.assignColor(isFirst ? BLACK : WHITE);
}