#include "unit.h"

Bishop::Bishop(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/bb.svg") : QIcon(":/icons/bw.svg");
    this->icon.pixmap(QSize(70,70));
}

QVector <QVector <QPoint>> Bishop::moves()
{
    QVector <QVector <QPoint>> moves;
    QVector <QPoint> currentMove;
    int unitX = this->getX();
    int unitY = this->getY();

    int allPossible[8] = {1,1,    -1,-1,    1,-1,    -1,1};

    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j++)
        {
            currentMove.push_back(QPoint(unitX += allPossible[i],unitY += allPossible[i+1]));
        }
        unitX = this->getX();
        unitY = this->getY();
        moves.push_back(currentMove);
        currentMove.clear();
    }
    return moves;
}

