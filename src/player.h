#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "settings.h"

class Player
{
private:
    char username[50];
    chessPlayerType youAre;

public:
    Player(const char *name);

    const char *getUsername() const;

    void assignColor(chessPlayerType color);

    chessPlayerType getColor() const;
};

#endif