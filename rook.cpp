#include "unit.h"

Rook::Rook(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/rb.svg") : QIcon(":/icons/rw.svg");
    this->icon.pixmap(QSize(70,70));
}

QVector <QVector <QPoint>> Rook::  moves()
{
    QVector <QVector <QPoint>> moves;
    QVector <QPoint> currentMove;

    int unitX = this->getX();
    int unitY = this->getY();

    int allPossible[8] = {1,0,    0,1,    -1,0,    0,-1};

    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j++)
        {
            unitX += allPossible[i];
            unitY += allPossible[i+1];
            currentMove.push_back( QPoint(unitX, unitY) );
        }
        unitX = this->getX();
        unitY = this->getY();
        moves.push_back(currentMove);
        currentMove.clear();
    }
    return moves;
}
