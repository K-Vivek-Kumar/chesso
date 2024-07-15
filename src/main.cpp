#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif

#include "player.h"
#include "chessboard.h"

std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> generatePossibleMoves(ChessBoard &board, chessPlayerType playerTurn)
{
    std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> moves;
    for (char file = 'a'; file <= 'h'; ++file)
    {
        for (char rank = '1'; rank <= '8'; ++rank)
        {
            char start[2] = {file, rank};
            ChessPiece piece = board.whichPiece(start);
            if (piece.color == (playerTurn == WHITE ? WHITE_COLOR : BLACK_COLOR))
            {
                for (char endFile = 'a'; endFile <= 'h'; ++endFile)
                {
                    for (char endRank = '1'; endRank <= '8'; ++endRank)
                    {
                        char end[2] = {endFile, endRank};
                        if (board.validate(start, end))
                        {
                            moves.push_back({{file, rank}, {endFile, endRank}});
                        }
                    }
                }
            }
        }
    }
    return moves;
}

void makeRandomMove(ChessBoard &board)
{
    std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> moves = generatePossibleMoves(board, board.playerTurn);
    if (!moves.empty())
    {
        std::srand(static_cast<unsigned>(std::time(0)));
        int index = std::rand() % moves.size();
        auto move = moves[index];
        char start[2] = {move.first.first, move.first.second};
        char end[2] = {move.second.first, move.second.second};
        board.makeMove(start, end);
        std::cout << "AI moved from " << start[0] << start[1] << " to " << end[0] << end[1] << std::endl;
    }
}

int main()
{
    Player player1("Vivek");
    Player player2("AI");
    ChessBoard board1(player1, player2);
    std::cout << player1.getUsername() << " got " << (player1.getColor() == WHITE ? "white" : "black") << " color.\n";
    std::cout << player2.getUsername() << " got " << (player2.getColor() == WHITE ? "white" : "black") << " color.\n";

    while (true)
    {
        std::cout << "Current turn: " << (board1.playerTurn == WHITE ? "White" : "Black") << std::endl;
        if (board1.playerTurn == player1.getColor())
        {
            std::cout << player1.getUsername() << " -> ";
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
            else if (s.length() == 4)
            {
                char start[2] = {s[0], s[1]};
                char end[2] = {s[2], s[3]};
                bool moveStatus = board1.validate(start, end);
                if (moveStatus)
                {
                    std::cout << "Move Placed Successfully" << std::endl;
                    board1.makeMove(start, end);
                    board1.playerTurn = board1.flipPlayerTurn();
                    std::cout << "Player turn flipped to: " << (board1.playerTurn == WHITE ? "White" : "Black") << std::endl;
                }
                else
                {
                    std::cout << "Move Not Possible" << std::endl;
                }
            }
        }
        else
        {
            makeRandomMove(board1);
            board1.playerTurn = board1.flipPlayerTurn();
            std::cout << "Player turn flipped to: " << (board1.playerTurn == WHITE ? "White" : "Black") << std::endl;
        }
    }
    return 0;
}
