#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <cstdlib>

#ifdef _WIN32
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif

#include "player.h"
#include "chessboard.h"

int main()
{
    Player player1("Vivek");
    Player player2("Kumar");
    ChessBoard board1(player1, player2);
    std::cout << player1.getUsername() << " got " << (player1.getColor() == WHITE ? "white" : "black") << " color.\n";
    std::cout << player2.getUsername() << " got " << (player2.getColor() == WHITE ? "white" : "black") << " color.\n";

    while (true)
    {
        if (board1.playerTurn == player1.getColor())
        {
            std::cout << player1.getUsername() << " -> ";
        }
        else
        {
            std::cout << player2.getUsername() << " -> ";
        }
        std::cout << "";
        std::string s;
        std::getline(std::cin, s);
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
        if (s.length() == 2)
        {
            char a[2] = {s[0], s[1]};
            ChessPiece piece = board1.whichPiece(a);
            board1.printPiece(piece);
        }
        else if (s.length() == 1)
        {
            if (s == "p")
            {
                board1.printBoard();
            }
            else if (s == "c")
            {
                system(CLEAR_COMMAND.c_str());
                continue;
            }
        }
    }
    return 0;
}