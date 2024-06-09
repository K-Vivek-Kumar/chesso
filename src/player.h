#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

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

#endif