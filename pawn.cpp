#include "unitsinfo.h"
#include "chess.h"

Pawn::Pawn(int xPos, int yPos, bool isBlack)
{
    construct(xPos, yPos, isBlack);
    this->icon = isBlack ? QIcon(":/icons/pb.svg") : QIcon(":/icons/pw.svg");
    this->icon.pixmap(QSize(70,70));
    this->direction = isBlack ? -1 : 1;
}

void Pawn::move(QPoint cell)
{
    if (isEnPassantMove())
    {
        setEnPassantPos();
    }
    doEnPassant();

    Unit::move(cell);
}

bool Pawn::isEnPassantMove()
{
    return this->unmoved && (Chess::mouseX - this->getX() == 2 || Chess::mouseX - this->getX() == -2);
}

void Pawn::setEnPassantPos()
{
    if(this->colorBlack)
        UnitsInfo::blackEnPassantPos.setX(this->getX() - this->direction), UnitsInfo::blackEnPassantPos.setY(this->getY());
    if(!this->colorBlack)
        UnitsInfo::whiteEnPassantPos.setX(this->getX() - this->direction), UnitsInfo::whiteEnPassantPos.setY(this->getY());
}

void Pawn::doEnPassant()
{
    if(this->colorBlack)
        if(QPoint(Chess::mouseX, Chess::mouseY) == UnitsInfo::whiteEnPassantPos)
            if(UnitsInfo::unitsAtField[UnitsInfo::whiteEnPassantPos.x() + this->direction][UnitsInfo::whiteEnPassantPos.y()] != nullptr)
                UnitsInfo::unitsAtField[UnitsInfo::whiteEnPassantPos.x() + this->direction][UnitsInfo::whiteEnPassantPos.y()] = nullptr;

    if(!this->colorBlack)
        if(QPoint(Chess::mouseX, Chess::mouseY) == UnitsInfo::blackEnPassantPos)
            if(UnitsInfo::unitsAtField[UnitsInfo::blackEnPassantPos.x() + this->direction][UnitsInfo::blackEnPassantPos.y()] != nullptr)
                UnitsInfo::unitsAtField[UnitsInfo::blackEnPassantPos.x() + this->direction][UnitsInfo::blackEnPassantPos.y()] = nullptr;
}

void Pawn::includeEnPassantPos(QVector<QVector<QPoint>> &moves)
{
    QPoint possibleEnPassant(this->getX() + direction, this->getY() - 1);
    if(possibleEnPassant == UnitsInfo::whiteEnPassantPos && this->colorBlack)
        moves.push_back({{possibleEnPassant}});

    possibleEnPassant = QPoint(this->getX() + direction, this->getY() + 1);
    if(possibleEnPassant == UnitsInfo::whiteEnPassantPos && this->colorBlack)
        moves.push_back({{possibleEnPassant}});

    possibleEnPassant = QPoint(this->getX() + direction, this->getY() - 1);
    if(possibleEnPassant == UnitsInfo::blackEnPassantPos && !this->colorBlack)
        moves.push_back({{possibleEnPassant}});

    possibleEnPassant = QPoint(this->getX() + direction, this->getY() + 1);
    if(possibleEnPassant == UnitsInfo::blackEnPassantPos && !this->colorBlack)
        moves.push_back({{possibleEnPassant}});
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

    if((x + direction >=0 && x + direction < 8) && (y-1 >= 0 && y-1 < 8))
    {
        if(UnitsInfo::unitsAtField[x + direction][y-1] != nullptr && UnitsInfo::unitsAtField[x + direction][y-1]->colorBlack != Chess::whosTurn)
        {
            currentMove.push_back(QPoint(x + direction, y-1));
            moves.push_back(currentMove);
            currentMove.clear();
        }
    }


    if((x + direction >=0 && x + direction < 8) && (y-1 >= 0 && y+1 < 8))
    {
        if(UnitsInfo::unitsAtField[x + direction][y+1] != nullptr && UnitsInfo::unitsAtField[x + direction][y+1]->colorBlack != Chess::whosTurn)
        {
            currentMove.push_back(QPoint(x + direction, y+1));
            moves.push_back(currentMove);
            currentMove.clear();
        }}


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
