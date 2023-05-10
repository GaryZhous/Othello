#include "humanplayer.h"

HumanPlayer::HumanPlayer(Color color) : Player(0, color)
{
    m_type = Player::HUMAN;
}

//Player::PlayerType HumanPlayer::getPlayerType()
//{
//    return PlayerType::HUMAN;
//}
