#ifndef AI_H
#define AI_H

#include "board/board.h"

class AI
{

public:
    AI(Board *currentBoard);

    Square *makeMove(Board *currentBoard);
    QVector<QVector<Square* > > temp;

private:
    int alphaBeta(Board *board, int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluateBoard(Board *currentBoard);

    Board *m_currentBoard;
};

#endif // AI_H
