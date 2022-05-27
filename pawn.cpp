#include "chess.h"
#include "paintboard.h"
#include "utils.h"
#include <QDebug>
#include <QPair>
QPair <QRect, QIcon> Pawn::promoteTo[4];
bool Pawn::promotionAvailable = false;
Unit* Pawn::forPromotion = nullptr;
Pawn::Pawn(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/pb.svg") : QIcon(":/icons/pw.svg");
    this->icon.pixmap(QSize(70,70));
    this->direction = isBlack ? -1 : 1;
}

void Pawn::clearEnPassantPos()
{
    UnitsInfo::EnPassantPos = QPoint(-1,-1);
}

bool Pawn::isPromotePos()
{
    if(this->colorBlack && this->getX() == 7)
        return true;
    if(!this->colorBlack && this->getX() == 0)
        return true;
    return false;
}

void Pawn::promote()
{

}

void Pawn::move(QPoint cell)
{
    if (isEnPassantMove())
        setEnPassantPos();

    doEnPassant();

    if(!this->unmoved)
        clearEnPassantPos();

    Unit::move(cell);

    if(isPromotePos())
    {
        forPromotion = UnitsInfo::unitsAtField[this->getX()][this->getY()];
        promotionAvailable = true;
    }
}

bool Pawn::isEnPassantMove()
{
    return this->unmoved && (Chess::mouseX - this->getX() == 2 || Chess::mouseX - this->getX() == -2);
}

void Pawn::setEnPassantPos()
{
    UnitsInfo::EnPassantPos = QPoint(this->getX() - this->direction, this->getY());
}

void Pawn::doEnPassant()
{
    QPoint mousePos(Chess::mouseX, Chess::mouseY);

    if(mousePos == UnitsInfo::EnPassantPos)
        if(UnitsInfo::unitsAtField[UnitsInfo::EnPassantPos.x() + this->direction][UnitsInfo::EnPassantPos.y()] != nullptr)
        {
            UnitsInfo::unitsAtField[UnitsInfo::EnPassantPos.x() + this->direction][UnitsInfo::EnPassantPos.y()]->~Unit();
            UnitsInfo::unitsAtField[UnitsInfo::EnPassantPos.x() + this->direction][UnitsInfo::EnPassantPos.y()] = nullptr;
        }
}

void Pawn::includeEnPassantPos(QVector<QVector<QPoint>> &moves)
{
    int x = this->getX();
    int y = this->getY();

    for(int i = x - this->direction,   j = y - 1;  j <= y + 1;   j += 2)
        if(QPoint(i,j) == UnitsInfo::EnPassantPos)
            moves.push_back({QPoint(i,j)});
}

QVector <QVector <QPoint>> Pawn::  moves()
{
    QVector <QVector <QPoint>> moves;
    QVector <QPoint> currentMove;

    int x = this->getX();
    int y = this->getY();
    int direction = this->colorBlack ? 1 : -1;
    int counter  =  this->unmoved + 1;

    includeEnPassantPos(moves);

    if(this->getX() >=1 && this->getX() < 7)
    {
        for (int i = this->getX() + direction, j = std::abs(this->getY() - 1); j <= this->getY()+1 ; j+=2)
        {
            if(j == 8)
                break;
            if(UnitsInfo::unitsAtField[i][j] != nullptr && UnitsInfo::unitsAtField[i][j]->colorBlack != this->colorBlack)
                moves.push_back({QPoint(i,j)});
        }
    }

    while (counter  >  0)
    {
        x += direction;
        if(UnitsInfo::unitsAtField[x][y] == nullptr)
            currentMove.push_back(QPoint(x,y));
        else break;
        counter--;
    }
    moves.push_back(currentMove);
    return moves;
}
