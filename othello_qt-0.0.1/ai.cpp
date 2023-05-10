#include "ai.h"

AI::AI(Board *currentBoard)
{
    m_currentBoard = currentBoard;
}

Square* AI::makeMove(Board *currentBoard)
{
    QVector<Square* > *legalMoves = new QVector<Square* >;

    currentBoard->getLegalMoves(legalMoves);

    Square *square;
    if (!legalMoves->isEmpty())
    {
        square  = legalMoves->first();
    }
    else
    {
        square = NULL;
    }
    currentBoard->makeMove(square->m_x, square->m_y);

    return square;
}

int AI::alphaBeta(Board *board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if ((depth = 0 || board->m_gameOver))
    {
        int boardValue = evaluateBoard(board);
        return boardValue;
    }

    QVector<Board *> possibleBoards = board->makeLegalMoves();

    if (maximizingPlayer == true)
    {
        foreach (Board *board, possibleBoards)
        {
            int newAlpha = alphaBeta(board, depth-1, alpha, beta, false);
            if (newAlpha >= alpha)
                alpha = newAlpha;

            if (alpha >= beta)
                break;
        }
        return alpha;
    }
    else if (maximizingPlayer == false)
    {
        foreach (Board *board, possibleBoards)
        {
            int newBeta = alphaBeta(board, depth-1, alpha, beta, false);
            if (newBeta <= beta)
            {
                beta = newBeta;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
        return alpha;
    }
    return -1;
}

int AI::evaluateBoard(Board *currentBoard)
{
    QVector<Square*> *legalMoves = nullptr;
    currentBoard->getLegalMoves(legalMoves);

    int numberOfLegalMoves = legalMoves->count();

    currentBoard->countDisks();

    return numberOfLegalMoves;
}
