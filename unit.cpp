#include "unitsinfo.h"
#include "utils.h"

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
    QVector<QVector<QRect>> moves = Utils::validMove(this->moves());

    for (int i = 0; i < moves.size(); i++)
        for (int j = 0; j < moves[i].size(); j++)
            if(cell == moves[i][j])
                return true;

    return false;
}

void Unit::move(QPoint cell)
{
    if (UnitsInfo::unitsAtField[cell.x()][cell.y()]!= nullptr)
        delete UnitsInfo::unitsAtField[cell.x()][cell.y()];

    this->unmoved = false;
    UnitsInfo::unitsAtField[cell.x()][cell.y()] = this;
    int x = this->getX();
    int y = this->getY();
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
    this->moves().~QVector();
}


