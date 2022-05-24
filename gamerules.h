#ifndef GAMERULES_H
#define GAMERULES_H
#include "unit.h"

class GameRules
{
public:

    static QVector<QVector<QRect>> validMove(QVector<QVector<QPoint>> allMoves);
};
#endif // GAMERULES_H
