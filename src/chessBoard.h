#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "types.h"
#include "player.h"

class ChessBoard
{
private:
    chessPlayerType playerTurn;
    ChessPiece board[8][8];

public:
    ChessBoard(Player &playerA, Player &playerB, Player *toStart = nullptr);
    void setToInitialConfiguration();
    void printBoard() const;
};

#endif