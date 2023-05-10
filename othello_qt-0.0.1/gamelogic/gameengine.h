#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTextEdit>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>

#include "board/board.h"
#include "player/player.h"
#include "player/computerplayer.h"
#include "player/humanplayer.h"
#include "ui/uigamescene.h"
#include "ai.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(QObject* parent, UIGameScene* uiGameScene, QTextEdit *eventList, QTextEdit *infoList);
    ~GameEngine();

    void registerHumanPlayer(HumanPlayer player);

    void startGame(int numberOfHumans = 1, double timeLimit = 10);

    Board *m_board;
    
public slots:
    void mouseReleased(QPointF point);
    void updateUI(int x, int y, Player::Color currentPlayer);

private:

    bool gameOver(void);

    bool m_gameOver;

    QString getGameStats(void);

    void makePass();

    void createPlayers(int numberOfHumans);

    void eventHandling(int x, int y);

    void togglePlayer();

    void showLegalMoves(void);

    QVector<Square* > *m_legalMoves;


    UIGameScene* m_uiGameScene;
    QTextEdit *m_eventList;
    QTextEdit *m_infoList;

    void revertAllowedUISquares(int x, int y);

    void updateInfoText(QString string);
    void updateEventText(QString string);

    int m_numberOfHumans;

    QList<int> m_gameEvents;

    int m_numberOfActualMoves;

    int m_numberOfTotalMoves;

    double m_timeLimit;

    double m_elapsedTime;

    double getThinkingTime();

    Player *m_currentPlayer;
    Player *m_opponentPlayer;

    QElapsedTimer m_thinkingTime;

    HumanPlayer* m_humanPlayerB;

    HumanPlayer* m_humanPlayerW;

    ComputerPlayer* m_computerPlayerB;
    ComputerPlayer* m_computerPlayerW;
    QList<Player *> players;


    AI *m_ai;


private slots:
    void counter();
};

#endif
