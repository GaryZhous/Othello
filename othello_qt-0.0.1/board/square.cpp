#include "square.h"

Square::Square(int x, int y)
{
    m_x = x;
    m_y = y;
    initSquare();
}

void Square::initSquare()
{
    m_currentOwner = Player::NONE;
    setSquareState(Square::BOARD);
}

Square::State Square::getSquareState(void)
{
    return m_squareState;
}

bool Square::isEmpty()
{
    if (m_squareState == BLACK || m_squareState == WHITE || m_currentOwner == Player::BLACK || m_currentOwner == Player::WHITE)
        return false;

    else if (m_currentOwner == Player::NONE || m_squareState == NONE || m_squareState == ALLOWED || m_squareState == SUGGESTED)
        return true;

    return false;
}

void Square::setSquareState(State state)
{
    m_squareState = state;
    switch (m_squareState) {
    case Square::BLACK:
        setOwner(Player::BLACK);
        break;
    case Square::WHITE:
        setOwner(Player::WHITE);
        break;
    default:
        break;
    }
}

Player::Color Square::getOwner()
{
    return m_currentOwner;
}

void Square::setOwner(Player::Color currentOwner)
{
    m_currentOwner = currentOwner;
}


