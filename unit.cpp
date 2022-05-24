#include "unitsinfo.h"
#include "gamerules.h"

void Unit::construct(int x, int y, bool isBlack)
{
    this->unmoved = true;
    this->x = x;
    this->y = y;
    this->colorBlack = isBlack;
}

int Unit::getX()
{
    return this->x;
}

int Unit::getY()
{
    return this->y;
}

bool Unit::isMoveOfTheUnit(QRect &cell)
{
    QVector<QVector<QRect>> moves = GameRules::validMove(this->moves());

    for (int i = 0; i < moves.size(); i++)
        for (int j = 0; j < moves[i].size(); j++)
            if(cell == moves[i][j])
                return true;

    return false;
}

void Unit::move(QPoint cell)
{
    this->unmoved = false;
    UnitsInfo::unitsAtField[cell.x()][cell.y()] = this;
    int x = this->x;
    int y = this->y;
    this->x = cell.x();
    this->y = cell.y();
    UnitsInfo::unitsAtField[x][y] = nullptr;
}

QVector <QVector <QPoint>> Unit::  moves()
{
    return {};
}

Unit::~Unit()
{
    this->icon.~QIcon();
}


