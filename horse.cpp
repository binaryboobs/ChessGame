#include "unit.h"

Horse::Horse(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/nb.svg") : QIcon(":/icons/nw.svg");
    this->icon.pixmap(QSize(70,70));
}

QVector <QVector <QPoint>> Horse:: moves()
{
    QVector <QVector <QPoint>> moves;

    int allPossible[16] = {-2,-1,   -2,1,  -1,2,   1,2,   2,1,    2,-1,    1,-2,   -1,-2};
    int unitX = this->getX();
    int unitY = this->getY();

    for(int i = 0; i < 16; i += 2)
    {
        moves.push_back({QPoint(unitX +allPossible[i], unitY + allPossible[i+1])});
    }
    return moves;
}
