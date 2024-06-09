#ifndef TYPES_H
#define TYPES_H

enum chessPieceType
{
    EMPTY,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING,
};

enum chessPlayerType
{
    WHITE,
    BLACK,
};

enum chessPieceColorType
{
    EMPTY_COLOR,
    WHITE_COLOR,
    BLACK_COLOR,
};

struct ChessPiece
{
    chessPieceColorType color;
    chessPieceType type;
};

#endif