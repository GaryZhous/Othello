#ifndef BOARD_H
#define BOARD_H


#define BOARD_SIZE 8

#include <QObject>
#include <QDebug>

#include "board/square.h"
#include "player/player.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(Player *currentPlayer, QObject *parent = 0);
    Board(const Board &board);

    // TODO move intitialization to constructor
    const int m_direction[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    Square *getSquare(int x, int y) const;
    Square::State getSquareState(int x, int y);

    void newBoard();

    void setPlayers();

    void countDisks(void);

    int m_numberOfBlackDisks;
    int m_numberOfWhiteDisks;
    int m_numberOfDisks;

    bool m_gameOver;

    bool legalMove(int x, int y);

    bool getLegalMoves(QVector<Square *> *legalMoves);

    QVector<Square* > *m_legalMoves;

    QVector<Board *> makeLegalMoves();

    void makeMove(int x, int y);
    //bool findLegalMoves(bool *legalMoves);

    bool undoMove();

    bool onBoard(int x, int y);

    Player::Color getOtherPlayer(Player *currentPlayer);




private:
    QVector<QVector<Square* > > m_boardMatrix;
    Player *m_currentPlayer;


signals:
    void signalBoardChanged(int x, int y, Player::Color color);

public slots:
};

#endif
