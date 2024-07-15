#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "types.h"
#include "player.h"

class ChessBoard
{
private:
    ChessPiece board[8][8];

public:
    chessPlayerType playerTurn;
    chessPlayerType flipPlayerTurn();
    ChessBoard(Player &playerA, Player &playerB, Player *toStart = nullptr);
    void setToInitialConfiguration();
    void printBoard() const;
    ChessPiece whichPiece(char place[2]);
    void printPiece(ChessPiece);
    bool validate(char start[2], char end[2]);
    bool validatePawnMove(int fromX, int fromY, int toX, int toY);
    bool validateBishopMove(int fromX, int fromY, int toX, int toY);
    bool validateQueenMove(int fromX, int fromY, int toX, int toY);
    bool validateRookMove(int fromX, int fromY, int toX, int toY);
    bool validateKingMove(int fromX, int fromY, int toX, int toY);
    bool validateKnightMove(int fromX, int fromY, int toX, int toY);
    bool makeMove(char start[2], char end[2]);
    bool isCheckmate();
    bool isCheck();
};

#endif