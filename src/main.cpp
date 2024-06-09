#include <iostream>

#include "player.h"
#include "chessboard.h"

int main()
{
    Player player1("Vivek");
    Player player2("Kumar");
    ChessBoard board1(player1, player2);
    std::cout << player1.getUsername() << " got " << (player1.getColor() == WHITE ? "white" : "black") << " color.\n";
    std::cout << player2.getUsername() << " got " << (player2.getColor() == WHITE ? "white" : "black") << " color.\n";
    board1.printBoard();
    return 0;
}