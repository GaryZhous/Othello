#include "player.h"

Player::Player(QObject *parent, Color color) : QObject(parent)
{
    m_color = color;
    m_type = UNKNOWN;
}

void Player::setPlayerColor(Player::Color color)
{
    m_color = color;
}

void Player::setPlayerType(Player::Type type)
{
    m_type = type;
}

