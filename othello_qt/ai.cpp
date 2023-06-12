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
    if (depth == 0 || board->m_gameOver)
    {
        int boardValue = evaluateBoard(board);
        return boardValue;
    }

    QVector<Board *> possibleBoards = board->makeLegalMoves();

    if (maximizingPlayer)
    {
        foreach (Board *nextBoard, possibleBoards)
        {
            int newAlpha = alphaBeta(nextBoard, depth-1, alpha, beta, false);
            if (newAlpha >= alpha)
            {
                alpha = newAlpha;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
        return alpha;
    }
    else
    {
        foreach (Board *nextBoard, possibleBoards)
        {
            int newBeta = alphaBeta(nextBoard, depth-1, alpha, beta, true);
            if (newBeta <= beta)
            {
                beta = newBeta;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
        return beta;
    }
}


int AI::evaluateBoard(Board *currentBoard)
{

    int numberOfBlackDisks = 0;
    int numberOfWhiteDisks = 0;
    QVector<Square*> h(8);
    temp.push_back(h);
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            temp[x].push_back(currentBoard->getSquare(x,y));

    Player::Color currentOwner;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            currentOwner = temp[x][y]->getOwner();
            if (currentOwner == Player::BLACK)
            {
                numberOfBlackDisks++;
            }
            else if (currentOwner == Player::WHITE)
            {
                numberOfWhiteDisks++;
            }
        }
    }
    return abs(numberOfWhiteDisks - numberOfBlackDisks);
}
