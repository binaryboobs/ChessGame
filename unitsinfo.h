#ifndef UNITSINFO_H
#define UNITSINFO_H
#include "unit.h"
class UnitsInfo
{
public:
    static QVector <QVector<Unit*>> unitsAtField;
    static QVector <QVector<Unit*>> WhiteUnits;
    static QVector <QVector<Unit*>> BlackUnits;

    static Unit* whiteKing;
    static Unit* blackKing;

    static QPoint rookPlace;

    static QPoint blackEnPassantPos;
    static QPoint whiteEnPassantPos;

    static void initializeEmptyUnitsField();
    static void setUnits();
    static void patchUnitsToField();


};
#endif // UNITSINFO_H
