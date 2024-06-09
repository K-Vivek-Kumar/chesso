#include <cstring>

#include "player.h"

Player::Player(const char *name)
{
    strncpy(username, name, sizeof(username));
    username[sizeof(username) - 1] = '\0';
}

const char *Player::getUsername() const
{
    return username;
}

void Player::assignColor(chessPlayer color)
{
    youAre = color;
}