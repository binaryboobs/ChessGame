#include "chess.h"
#include "utils.h"

King::King(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/kb.svg") : QIcon(":/icons/kw.svg");
    this->icon.pixmap(QSize(70,70));
}

QVector <QVector <QPoint>> King::  moves()
{
    QVector <QVector <QPoint>> moves;
    QVector <QPoint> currentMove;

    if(this->unmoved)
    {
        moves.push_back(findRookingSpots());
    }

    int x = this->getX() - 1;
    int y = this->getY() - 1;

    for(int i = x; i < x + 3; i++){
        for(int j = y; j < y + 3; j++){
            currentMove.push_back(QPoint(i,j));
            moves.push_back(currentMove);
            currentMove.clear();
        }
    }
    return moves;
}

void King::move(QPoint cell)
{
    goRooking();
    Unit::move(cell);
}

void King::goRooking()
{
    if (Chess::mouseY == this->getY() - 2)
    {
        UnitsInfo::unitsAtField[Chess::currentUnit->x][0]->move(UnitsInfo::rookPlace);
    }
    if (Chess::mouseY == this->getY() + 2)
    {
        UnitsInfo::unitsAtField[Chess::currentUnit->x][7]->move(UnitsInfo::rookPlace);
    }
}

QVector <QPoint> King::findRookingSpots()
{
    int kingX = this->getX();
    int kingY = this->getY();
    QVector<QPoint> rookingSteps;

    if(this->unmoved)
    {
        for(int i = 0, addPoint = -2, rookGo = -1;           i < 8;          i+=7, addPoint *= -1, rookGo *= -1)
        {
            if(UnitsInfo::unitsAtField[kingX][i] != nullptr)
                if(UnitsInfo::unitsAtField[kingX][i]->unmoved)
                    if(Utils::isClearArea(UnitsInfo::unitsAtField[kingX][i], this))
                        rookingSteps.push_back(QPoint(kingX,kingY + addPoint)), UnitsInfo::rookPlace.setX(kingX), UnitsInfo::rookPlace.setY(kingY + rookGo);
        }

    }

    return rookingSteps;
}
