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

    // TODO make private and use getter. Square position shouldn't be changed.
    /**
     * @brief m_x m_y are the positions on the board.
     */
    int m_x;
    int m_y;

    /**
     * @brief getSquareState returns the current state of the square stored in m_squareState.
     * @return m_squareState which can be one of the enum State.
     */
    State getSquareState(void);

    /**
     * @brief isEmpty determins if a square is either of enum State {BOARD, ALLOWED or SUGGESTED}
     * if so, the function returns true.
     * @return true if square is not occupied by a player.
     */
    bool isEmpty();

    /**
     * @brief setSquareState sets the state with the provided enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED}
     * @param state
     */
    void setSquareState(State state);

    Player::Color getOwner(void);
    void setOwner(Player::Color currentOwner);


private:
    void initSquare();

    /**
     * @brief m_squareState current state of the square. Values of enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED}
     */
    State m_squareState;

    /**
     * @brief m_currentOwner color of the player owning the square currently.
     */
    Player::Color m_currentOwner;


};

#endif // SQUARE_H
