#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(Player::Color color);

    //virtual PlayerType getPlayerType();

signals:

public slots:
};

#endif // COMPUTERPLAYER_H
