#include <random>
#include <ctime>
#include <iostream>
#include <vector>

#include "chessboard.h"

ChessBoard::ChessBoard(Player &playerA, Player &playerB, Player *toStart)
{
    std::srand(static_cast<unsigned>(std::time(0)));
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
    std::cout << "  ==========================\n";

    for (int row = 0; row < 8; ++row)
    {
        std::cout << 8 - row << " || ";

        for (int col = 0; col < 8; ++col)
        {
            std::string squareColor = ((row + col) % 2 == 0) ? lightColor : darkColor;
            std::string pieceColor = (board[row][col].color == WHITE_COLOR) ? "\033[1;37m" : "\033[0;36m";

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
    std::cout << "  ==========================\n";
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

ChessPiece ChessBoard::whichPiece(char place[2])
{
    int col = fileToCol(place[0]);
    int row = rankToRow(place[1]);
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

bool playerTypeVSPieceColorType(chessPlayerType player, ChessPiece piece)
{
    return (player == chessPlayerType::BLACK) ? piece.color == chessPieceColorType::BLACK_COLOR : piece.color == chessPieceColorType::WHITE_COLOR;
}

bool ChessBoard::isCheck()
{
    int kingX, kingY;
    chessPieceColorType kingColor = (playerTurn == WHITE) ? WHITE_COLOR : BLACK_COLOR;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col].type == KING && board[row][col].color == kingColor)
            {
                kingX = col;
                kingY = row;
                break;
            }
        }
    }
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece piece = board[row][col];
            if (piece.color != kingColor && piece.color != EMPTY_COLOR)
            {
                int start[2] = {col, row};
                int end[2] = {kingX, kingY};
                char startChar[2] = {static_cast<char>(start[0] + 'a'), static_cast<char>('8' - start[1])};
                char endChar[2] = {static_cast<char>(end[0] + 'a'), static_cast<char>('8' - end[1])};
                if (validate(startChar, endChar))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isCheckmate()
{
    if (!isCheck())
    {
        return false;
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessPiece piece = board[row][col];
            if (playerTypeVSPieceColorType(playerTurn, piece))
            {
                for (int destRow = 0; destRow < 8; ++destRow)
                {
                    for (int destCol = 0; destCol < 8; ++destCol)
                    {
                        int start[2] = {col, row};
                        int end[2] = {destCol, destRow};
                        char startChar[2] = {static_cast<char>(start[0] + 'a'), static_cast<char>('8' - start[1])};
                        char endChar[2] = {static_cast<char>(end[0] + 'a'), static_cast<char>('8' - end[1])};
                        if (validate(startChar, endChar))
                        {
                            ChessBoard copy = *this;
                            copy.makeMove(startChar, endChar);
                            if (!copy.isCheck())
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessBoard::validate(char start[2], char end[2])
{
    ChessPiece toMoveFrom = this->whichPiece(start);
    if (!playerTypeVSPieceColorType(this->playerTurn, toMoveFrom))
    {
        return false;
    }
    ChessPiece toMoveTo = this->whichPiece(end);
    if (playerTypeVSPieceColorType(this->playerTurn, toMoveTo))
    {
        return false;
    }
    int fromX = fileToCol(start[0]);
    int fromY = rankToRow(start[1]);
    int toX = fileToCol(end[0]);
    int toY = rankToRow(end[1]);

    switch (toMoveFrom.type)
    {
    case PAWN:
        return validatePawnMove(fromX, fromY, toX, toY);
    case KNIGHT:
        return validateKnightMove(fromX, fromY, toX, toY);
    case ROOK:
        return validateRookMove(fromX, fromY, toX, toY);
    case BISHOP:
        return validateBishopMove(fromX, fromY, toX, toY);
    case QUEEN:
        return validateQueenMove(fromX, fromY, toX, toY);
    case KING:
        return validateKingMove(fromX, fromY, toX, toY);
    default:
        return false;
    }
}

bool ChessBoard::validatePawnMove(int fromX, int fromY, int toX, int toY)
{
    int direction = (this->playerTurn == WHITE) ? -1 : 1;
    if (fromX == toX && board[toY][toX].type == EMPTY && (toY - fromY == direction || (fromY == (this->playerTurn == WHITE ? 6 : 1) && toY - fromY == 2 * direction)))
    {
        return true;
    }
    if (std::abs(toX - fromX) == 1 && toY - fromY == direction && board[toY][toX].type != EMPTY && board[toY][toX].color != board[fromY][fromX].color)
    {
        return true;
    }
    return false;
}

bool ChessBoard::validateKnightMove(int fromX, int fromY, int toX, int toY)
{
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

bool ChessBoard::validateRookMove(int fromX, int fromY, int toX, int toY)
{
    if (fromX != toX && fromY != toY)
    {
        return false;
    }

    int xDirection = (toX > fromX) ? 1 : (toX < fromX) ? -1
                                                       : 0;
    int yDirection = (toY > fromY) ? 1 : (toY < fromY) ? -1
                                                       : 0;

    for (int x = fromX + xDirection, y = fromY + yDirection; x != toX || y != toY; x += xDirection, y += yDirection)
    {
        if (board[y][x].type != EMPTY)
        {
            return false;
        }
    }

    return true;
}

bool ChessBoard::validateBishopMove(int fromX, int fromY, int toX, int toY)
{
    if (std::abs(fromX - toX) != std::abs(fromY - toY))
    {
        return false;
    }

    int xDirection = (toX > fromX) ? 1 : -1;
    int yDirection = (toY > fromY) ? 1 : -1;

    for (int x = fromX + xDirection, y = fromY + yDirection; x != toX && y != toY; x += xDirection, y += yDirection)
    {
        if (board[y][x].type != EMPTY)
        {
            return false;
        }
    }

    return true;
}

bool ChessBoard::validateQueenMove(int fromX, int fromY, int toX, int toY)
{
    return validateRookMove(fromX, fromY, toX, toY) || validateBishopMove(fromX, fromY, toX, toY);
}

bool ChessBoard::validateKingMove(int fromX, int fromY, int toX, int toY)
{
    return std::abs(toX - fromX) <= 1 && std::abs(toY - fromY) <= 1;
}

bool ChessBoard::makeMove(char start[2], char end[2])
{
    if (validate(start, end))
    {
        int fromX = fileToCol(start[0]);
        int fromY = rankToRow(start[1]);
        int toX = fileToCol(end[0]);
        int toY = rankToRow(end[1]);

        ChessPiece tempPiece = board[toY][toX];
        board[toY][toX] = board[fromY][fromX];
        board[fromY][fromX] = {EMPTY_COLOR, EMPTY};

        if (isCheck())
        {
            board[fromY][fromX] = board[toY][toX];
            board[toY][toX] = tempPiece;
            return false;
        }

        this->flipPlayerTurn();
        return true;
    }
    return false;
}

chessPlayerType ChessBoard::flipPlayerTurn()
{
    if (this->playerTurn == WHITE)
    {
        return BLACK;
    }
    else
    {
        return WHITE;
    }
}
