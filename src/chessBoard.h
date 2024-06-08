#ifndef CHESSBOARD_H
#define CHESSBOARD_H

enum chessPiece
{
    EMPTY,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING,
};

enum chessPlayer
{
    WHITE,
    BLACK,
};

class Player
{
private:
    char username[50];
    chessPlayer youAre;

public:
    Player(const char *name);

    const char *getUsername() const;

    void assignColor(chessPlayer color);
};

class ChessBoard
{
private:
    chessPlayer playerTurn;
    chessPiece board[8][8];

public:
    ChessBoard(Player playerA, Player playerB);
};

#endif