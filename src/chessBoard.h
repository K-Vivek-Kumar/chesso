#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "types.h"
#include "player.h"

class ChessBoard
{
private:
    chessPlayer playerTurn;
    chessPiece board[8][8];

public:
    ChessBoard(Player &playerA, Player &playerB);
};

#endif