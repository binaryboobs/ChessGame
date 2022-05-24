#include "unitsinfo.h"
#include "chess.h"
#include "gamerules.h"

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
    if (Chess::mouseY == int(this->y) - 2)
    {
        UnitsInfo::unitsAtField[Chess::currentUnit->x][0]->move(UnitsInfo::rookPlace);
    }
    if (Chess::mouseY == int(this->y) + 2)
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
        if(kingY == 3)
        {
            if(UnitsInfo::unitsAtField[kingX][kingY - 1] == nullptr)
                if(UnitsInfo::unitsAtField[kingX][kingY - 2] == nullptr)
                    if(UnitsInfo::unitsAtField[kingX][kingY - 3] != nullptr && UnitsInfo::unitsAtField[kingX][kingY - 3]->unmoved)
                        rookingSteps.push_back(QPoint(kingX,kingY - 2)), UnitsInfo::rookPlace.setX(kingX), UnitsInfo::rookPlace.setY(kingY - 1);

            if(UnitsInfo::unitsAtField[kingX][kingY + 1] == nullptr)
                if(UnitsInfo::unitsAtField[kingX][kingY + 2] == nullptr)
                    if(UnitsInfo::unitsAtField[kingX][kingY + 3] == nullptr)
                        if (UnitsInfo::unitsAtField[kingX][kingY + 4] != nullptr && UnitsInfo::unitsAtField[kingX][kingY + 4]->unmoved)
                            rookingSteps.push_back(QPoint(kingX,kingY + 2)), UnitsInfo::rookPlace.setX(kingX), UnitsInfo::rookPlace.setY(kingY + 1);

        }
        if(kingY == 4)
        {
            if(UnitsInfo::unitsAtField[kingX][kingY + 1] == nullptr)
                if(UnitsInfo::unitsAtField[kingX][kingY + 2] == nullptr)
                    if(UnitsInfo::unitsAtField[kingX][kingY + 3] != nullptr && UnitsInfo::unitsAtField[kingX][kingY + 3]->unmoved)
                        rookingSteps.push_back(QPoint(kingX,kingY + 2)), UnitsInfo::rookPlace.setX(kingX), UnitsInfo::rookPlace.setY(kingY + 1);

            if(UnitsInfo::unitsAtField[kingX][kingY - 1] == nullptr)
                if(UnitsInfo::unitsAtField[kingX][kingY - 2] == nullptr)
                    if(UnitsInfo::unitsAtField[kingX][kingY - 3] == nullptr)
                        if (UnitsInfo::unitsAtField[kingX][kingY - 4] != nullptr && UnitsInfo::unitsAtField[kingX][kingY - 4]->unmoved)
                            rookingSteps.push_back(QPoint(kingX,kingY - 2)), UnitsInfo::rookPlace.setX(kingX), UnitsInfo::rookPlace.setY(kingY - 1);

        }
    }

    return rookingSteps;
}
