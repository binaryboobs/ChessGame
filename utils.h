#ifndef UTILS_H
#define UTILS_H
#include "chess.h"
#include "paintboard.h"

class Utils
{
public:
    static bool isGameArea(int x, int y);
    static bool firstClick();
    static bool secondClick();
    static void captureUnit();
    static bool clickedAnotherUnit();
    static bool isClearArea(Unit *pos1, Unit *pos2);
    static Unit *setNewUnit(int chosen);
    static QVector<QVector<QRect>> validMove(QVector<QVector<QPoint>> allMoves);
};

#endif // UTILS_H
