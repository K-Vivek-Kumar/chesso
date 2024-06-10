#include <random>
#include <ctime>
#include <iostream>

#include "chessboard.h"

ChessBoard::ChessBoard(Player &playerA, Player &playerB, Player *toStart)
{
    std::srand(static_cast<unsigned>(time(0)));
    bool isFirst = std::rand() % 2 == 0;
    playerA.assignColor(isFirst ? WHITE : BLACK);
    playerB.assignColor(isFirst ? BLACK : WHITE);

    if (toStart != nullptr)
    {
        if (toStart == &playerA)
        {
            playerA.assignColor(WHITE);
            playerB.assignColor(BLACK);
        }
        else
        {
            playerA.assignColor(BLACK);
            playerB.assignColor(WHITE);
        }
    }

    playerTurn = WHITE;

    this->setToInitialConfiguration();
}

void ChessBoard::setToInitialConfiguration()
{
    board[0][0] = board[0][7] = {BLACK_COLOR, ROOK};
    board[0][1] = board[0][6] = {BLACK_COLOR, KNIGHT};
    board[0][2] = board[0][5] = {BLACK_COLOR, BISHOP};
    board[0][3] = {BLACK_COLOR, QUEEN};
    board[0][4] = {BLACK_COLOR, KING};
    for (int i = 0; i < 8; i++)
    {
        board[1][i] = {BLACK_COLOR, PAWN};
    }

    board[7][0] = board[7][7] = {WHITE_COLOR, ROOK};
    board[7][1] = board[7][6] = {WHITE_COLOR, KNIGHT};
    board[7][2] = board[7][5] = {WHITE_COLOR, BISHOP};
    board[7][3] = {WHITE_COLOR, QUEEN};
    board[7][4] = {WHITE_COLOR, KING};
    for (int i = 0; i < 8; i++)
    {
        board[6][i] = {WHITE_COLOR, PAWN};
    }

    for (int row = 2; row < 6; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            board[row][col] = {EMPTY_COLOR, EMPTY};
        }
    }
}

void ChessBoard::printBoard() const
{
    const std::string lightColor = "\033[1;37m";
    const std::string darkColor = "\033[0;36m";
    const std::string resetColor = "\033[0m";

    std::cout << "     a b c d e f g h\n";
    std::cout << "==========================\n";

    for (int row = 0; row < 8; ++row)
    {
        std::cout << 8 - row << " || ";

        for (int col = 0; col < 8; ++col)
        {
            std::string squareColor;
            if ((row + col) % 2 == 0)
            {
                squareColor = lightColor;
            }
            else
            {
                squareColor = darkColor;
            }

            std::string pieceColor;
            if (board[row][col].color == WHITE_COLOR)
            {
                pieceColor = "\033[1;37m";
            }
            else
            {
                pieceColor = "\033[0;36m";
            }

            switch (board[row][col].type)
            {
            case EMPTY:
                std::cout << squareColor << "- ";
                break;
            case PAWN:
                std::cout << pieceColor << "p ";
                break;
            case ROOK:
                std::cout << pieceColor << "r ";
                break;
            case KNIGHT:
                std::cout << pieceColor << "k ";
                break;
            case BISHOP:
                std::cout << pieceColor << "b ";
                break;
            case QUEEN:
                std::cout << pieceColor << "q ";
                break;
            case KING:
                std::cout << pieceColor << "K ";
                break;
            }
            std::cout << resetColor;
        }
        std::cout << " || " << 8 - row;
        std::cout << std::endl;
    }
    std::cout << "==========================\n";
    std::cout << "     a b c d e f g h\n";
}

int fileToCol(char file)
{
    return file - 'a';
}

int rankToRow(char rank)
{
    return 8 - (rank - '0');
}

bool isWithinBounds(int row, int col)
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool ChessBoard::validateMove(int startRow, int startCol, int endRow, int endCol) const
{
    if (!isWithinBounds(startRow, startCol) || !isWithinBounds(endRow, endCol))
    {
        return false;
    }
    if (startRow == endRow && startCol == endCol)
    {
        return false;
    }
    return true;
}

ChessPiece ChessBoard::whichPiece(char place[2])
{
    int col = fileToCol(place[0]);
    int row = rankToRow(place[1]);

    if (!isWithinBounds(row, col))
    {
        throw std::out_of_range("Position out of bounds");
    }

    return board[row][col];
}

void ChessBoard::printPiece(ChessPiece piece)
{
    std::cout << "Chesso says: ";

    switch (piece.color)
    {
    case WHITE_COLOR:
        std::cout << "White";
        break;
    case BLACK_COLOR:
        std::cout << "Black";
        break;
    case EMPTY_COLOR:
        std::cout << "Empty";
        break;
    }

    std::cout << " ";

    switch (piece.type)
    {
    case EMPTY:
        std::cout << "";
        break;
    case PAWN:
        std::cout << "Pawn";
        break;
    case ROOK:
        std::cout << "Rook";
        break;
    case KNIGHT:
        std::cout << "Knight";
        break;
    case BISHOP:
        std::cout << "Bishop";
        break;
    case QUEEN:
        std::cout << "Queen";
        break;
    case KING:
        std::cout << "King";
        break;
    }

    std::cout << std::endl;
}