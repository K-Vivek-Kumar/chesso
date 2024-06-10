#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "types.h"
#include "player.h"

class ChessBoard
{
private:
    ChessPiece board[8][8];
    bool validateMove(int, int, int, int) const;

public:
    chessPlayerType playerTurn;
    ChessBoard(Player &playerA, Player &playerB, Player *toStart = nullptr);
    void setToInitialConfiguration();
    void printBoard() const;
    ChessPiece whichPiece(char place[2]);
    void printPiece(ChessPiece);
};

#endif