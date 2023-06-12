#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(Color color) : Player(0, color)
{
    m_type = Player::COMPUTER;
}
