#include "utils.h"
#include "chess.h"
#include "paintboard.h"
#include "gamerules.h"
#include "unitsinfo.h"

bool Utils::isGameArea(int x, int y)
{
    if((x >= 0 && x < 8) && (y >= 0 && y < 8))
        return true;
    return false;
}

bool Utils::firstClick()
{
    return Chess::currentUnit == nullptr && UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY] !=nullptr;
}

bool Utils::secondClick()
{
    return Chess::currentUnit != nullptr && Chess::currentUnit->colorBlack == Chess::whosTurn;
}

void Utils::captureUnit()
{
    Chess::currentUnit = UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY];

    if(Chess::currentUnit->colorBlack  == Chess::whosTurn)
        PaintBoard::moves = GameRules::validMove(Chess::currentUnit->moves());
    else
        Chess::currentUnit = nullptr;
}

bool Utils::clickedAnotherUnit()
{
    return UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY] != nullptr && UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY]->colorBlack == Chess::whosTurn;
}
