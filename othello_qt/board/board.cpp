#include "board.h"

Board::Board(Player *currentPlayer, QObject *parent) : QObject(parent),
  m_boardMatrix(BOARD_SIZE, QVector<Square* >(BOARD_SIZE))
{
    m_currentPlayer = currentPlayer;
    newBoard();
}

Board::Board(const Board &board)
{
    m_legalMoves = new QVector<Square* >;

    // copy the board
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            m_boardMatrix[x][y] = board.getSquare(x,y);

    m_gameOver = board.m_gameOver;
}

Square *Board::getSquare(int x, int y) const
{
    return m_boardMatrix[x][y];
}

Square::State Board::getSquareState(int x, int y)
{
    return m_boardMatrix[x][y]->getSquareState();
}

void Board::newBoard()
{
    m_legalMoves = new QVector<Square* >;

    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            m_boardMatrix[x][y] = new Square(x,y);

    m_boardMatrix[BOARD_SIZE/2-1][BOARD_SIZE/2-1]->setSquareState(Square::WHITE);
    m_boardMatrix[BOARD_SIZE/2-1][BOARD_SIZE/2]->setSquareState(Square::BLACK);
    m_boardMatrix[BOARD_SIZE/2][BOARD_SIZE/2-1]->setSquareState(Square::BLACK);
    m_boardMatrix[BOARD_SIZE/2][BOARD_SIZE/2]->setSquareState(Square::WHITE);

    m_numberOfBlackDisks = 2;
    m_numberOfWhiteDisks = 2;
    m_numberOfDisks = 4;

    m_gameOver = false;
}

void Board::countDisks(void)
{
    m_numberOfBlackDisks = 0;
    m_numberOfWhiteDisks = 0;
    m_numberOfDisks = 0;


    Player::Color currentOwner;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            currentOwner = m_boardMatrix[x][y]->getOwner();
            if (currentOwner == Player::BLACK)
            {
                m_numberOfBlackDisks++;
                m_numberOfDisks++;
            }
            else if (currentOwner == Player::WHITE)
            {
                m_numberOfWhiteDisks++;
                m_numberOfDisks++;
            }
        }
    }
    qDebug() << "There are" << m_numberOfBlackDisks << "Black disks";
    qDebug() << "There are" << m_numberOfWhiteDisks << "White disks";
    qDebug() << "There are" << m_numberOfDisks << "total disks";
}

bool Board::legalMove(int x, int y)
{
    if(!onBoard(x, y))
    {
        return false;
    }
    if (!m_boardMatrix[x][y]->isEmpty())
    {
        return false;
    }
    bool moveLegal = false;
    for(int dir = 0; dir < BOARD_SIZE; dir++)
    {
        int dx = m_direction[dir][0];
        int dy = m_direction[dir][1];
        int tx = x + 2*dx;
        int ty = y + 2*dy;
        // need to be at least 2 grids away from the edge
        if (!onBoard(tx, ty))
            continue;
        if (m_boardMatrix[x+dx][y+dy]->getOwner() != getOtherPlayer(m_currentPlayer))
            continue;

        while(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == getOtherPlayer(m_currentPlayer))
        {
            tx += dx;
            ty += dy;
        }

        if(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == m_currentPlayer->m_color)
        {
            moveLegal = true;
            break;
        }
    }
    return moveLegal;

}

bool Board::getLegalMoves(QVector<Square* > *legalMoves)
{
    if (legalMoves == NULL)
    {
        legalMoves = new QVector<Square* >;
    }
    else
    {
        legalMoves->clear();
    }

    Square *allowedSquare = NULL;
    bool legalMovesAvailable = false;
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {
            if (legalMove(x, y))
            {
                allowedSquare = m_boardMatrix[x][y];

                allowedSquare->setSquareState(Square::ALLOWED);

                legalMoves->append(allowedSquare);
                legalMovesAvailable = true;
            }
        }
    }
    m_legalMoves = legalMoves;
    return legalMovesAvailable;
}

QVector<Board *> Board::makeLegalMoves()
{
    QVector<Board *> possibleBoards(1);

    getLegalMoves(NULL);

    foreach (Square *square, *m_legalMoves)
    {
        Board *tempBoard = new Board(*this);
        tempBoard->makeMove(square->m_x, square->m_y);
        possibleBoards.append(tempBoard);
    }
}

void Board::makeMove(int x, int y)
{
    // TODO update number of moves if valid;
    // TODO append to a tree?!

    for(int dir = 0; dir < BOARD_SIZE; dir++)
    {
        int dx = m_direction[dir][0];
        int dy = m_direction[dir][1];
        int tx = x + 2*dx;
        int ty = y + 2*dy;
        // need to be at least 2 grids away from the edge
        if (!onBoard(tx, ty))
        {
            continue;
        }
        // oppenent piece must be adjacent in the current direction
        if (m_boardMatrix[x+dx][y+dy]->getOwner() != getOtherPlayer(m_currentPlayer))
        {
            continue;
        }
        // as long as we stay on the board going in the current direction, we search for the surrounding disk
        while(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == getOtherPlayer(m_currentPlayer))
        {
            tx += dx;
            ty += dy;
        }
        // if we are still on the board and we found the surrounding disk in the current direction
        // the move is legal.

        // go back and flip the pieces if move is legal
        if(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == m_currentPlayer->m_color)
        {
            tx -= dx;
            ty -= dy;

            while(m_boardMatrix[tx][ty]->getOwner() == getOtherPlayer(m_currentPlayer))
            {
                //qDebug() << "Flipping" << tx << "," << ty;
                m_boardMatrix[tx][ty]->setOwner(m_currentPlayer->m_color);
                if (m_currentPlayer->m_color == Player::BLACK)
                {
                    //updateUI(tx, ty, UISquare::BLACK, Player::BLACK);
                    // TODO: avoid emit if AI move
                    emit signalBoardChanged(tx, ty, Player::BLACK);
                }
                else
                {
                    //updateUI(tx, ty, UISquare::WHITE, Player::WHITE);
                    // TODO: avoid emit if AI move
                    emit signalBoardChanged(tx, ty, Player::WHITE);
                }

                tx -= dx;
                ty -= dy;
            }
            // set color of placed disk to current player
            m_boardMatrix[x][y]->setOwner(m_currentPlayer->m_color);

            // TODO this needs some improvement - see also inside while loop
            if (m_currentPlayer->m_color == Player::BLACK)
            {
                //updateUI(tx, ty, UISquare::BLACK, Player::BLACK);
                // TODO: avoid emit if AI move
                emit signalBoardChanged(x, y, Player::BLACK);
            }
            else
            {
                //updateUI(tx, ty, UISquare::WHITE, Player::WHITE);
                // TODO: avoid emit if AI move
                emit signalBoardChanged(x, y, Player::WHITE);
            }

        }
    }

    //m_boardStack<Board*
}

bool Board::onBoard(int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

Player::Color Board::getOtherPlayer(Player *currentPlayer)
{
    if (currentPlayer->m_color == Player::BLACK)
    {
        return Player::WHITE;
    }
    else if (currentPlayer->m_color == Player::WHITE)
    {
        return Player::BLACK;
    }
    else if (currentPlayer->m_color == Player::NONE)
    {
        qDebug() << "Board::getOtherPlayer" << "Player::NONE?! Debug this";
    }
}
