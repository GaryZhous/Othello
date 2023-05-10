#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPoint>
#include <QDebug>

#include "player/player.h"

class Square
{

public:
    Square(int x, int y);

    enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    int m_x;
    int m_y;

    State getSquareState(void);

    bool isEmpty();

    void setSquareState(State state);

    Player::Color getOwner(void);
    void setOwner(Player::Color currentOwner);


private:
    void initSquare();

    State m_squareState;

    Player::Color m_currentOwner;


};

#endif // SQUARE_H
