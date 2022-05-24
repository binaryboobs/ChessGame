#include "unitsinfo.h"

Unit* UnitsInfo::blackKing;
Unit* UnitsInfo::whiteKing;

QPoint UnitsInfo::rookPlace;

QPoint UnitsInfo::blackEnPassantPos;
QPoint UnitsInfo::whiteEnPassantPos;

QVector <QVector<Unit*>> UnitsInfo::unitsAtField = {};
QVector <QVector<Unit*>> UnitsInfo::BlackUnits = {};
QVector <QVector<Unit*>> UnitsInfo::WhiteUnits = {};


void UnitsInfo::initializeEmptyUnitsField()
{
    for(int x = 0; x < 8; x++)
    {
        QVector <Unit*> current;
        for(int y = 0; y < 8; y++)
        {
            current.push_back(nullptr);
        }
        UnitsInfo::unitsAtField.push_back(current);
        current.clear();
    }
}

void UnitsInfo::setUnits()
{
    UnitsInfo::BlackUnits =
    {
        {new Rook(0,0,true), new Horse(0,1,true), new Bishop(0,2,true), new Queen(0,3,true), new King(0,4,true),new Bishop(0,5,true),new Horse(0,6,true),new Rook(0,7,true)},
        {new Pawn(1,0,true), new Pawn(1,1,true), new Pawn(1,2,true), new Pawn(1,3,true), new Pawn(1,4,true), new Pawn(1,5,true), new Pawn(1,6,true), new Pawn(1,7,true),}
    };
    UnitsInfo::WhiteUnits =
    {
        {new Pawn(6,0,false), new Pawn(6,1,false), new Pawn(6,2,false), new Pawn(6,3,false), new Pawn(6,4,false), new Pawn(6,5,false), new Pawn(6,6,false), new Pawn(6,7,false),},
        {new Rook(7,0,false), new Horse(7,1,false), new Bishop(7,2,false), new King(7,3,false), new Queen(7,4,false),new Bishop(7,5,false),new Horse(7,6,false),new Rook(7,7,false)}
    };
}

void UnitsInfo::patchUnitsToField()
{
    for(int row1 = 0, row2 = 1, row6 = 6, row7 = 7; row1 < 1; row1++)
    {
        for (int j = 0; j < 8; j++)
        {
            UnitsInfo::unitsAtField[row1][j] = UnitsInfo::BlackUnits[0][j];
            UnitsInfo::unitsAtField[row2][j] = UnitsInfo::BlackUnits[1][j];
            UnitsInfo::unitsAtField[row6][j] = UnitsInfo::WhiteUnits[0][j];
            UnitsInfo::unitsAtField[row7][j] = UnitsInfo::WhiteUnits[1][j];
        }

    }
}
