#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    enum Color {NONE, BLACK, WHITE} m_color;
    enum Type {UNKNOWN, HUMAN, COMPUTER} m_type;

    explicit Player(QObject *parent = 0, Color color = NONE);

    void setPlayerColor(Color color);
    void setPlayerType(Type type);

    //virtual PlayerType getPlayerType();


signals:

public slots:
};

#endif // PLAYER_H
