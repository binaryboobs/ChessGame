#include "utils.h"

bool Utils::isGameArea(int x, int y)
{
    if((x >= 0 && x < 8) && (y >= 0 && y < 8))
        return true;
    return false;
}

bool Utils::firstClick()
{
    return Chess::currentUnit == nullptr;
}

bool Utils::secondClick()
{
    return Chess::currentUnit != nullptr && Chess::currentUnit->colorBlack == Chess::whosTurn;
}

void Utils::captureUnit()
{
    Chess::currentUnit = UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY];

    if(Chess::currentUnit->colorBlack  == Chess::whosTurn)
        PaintBoard::moves = Utils::validMove(Chess::currentUnit->moves());
    else
        Chess::currentUnit = nullptr;
}

bool Utils::clickedAnotherUnit()
{
    return UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY] != nullptr && UnitsInfo::unitsAtField[Chess::mouseX][Chess::mouseY]->colorBlack == Chess::whosTurn;
}

bool Utils::isClearArea(Unit *pos1, Unit *pos2)
{
    QPoint firstPos(pos1->getX() , pos1->getY());
    QPoint secondPos(pos2->getX(), pos2->getY());

        for(int j = std::min(firstPos.y(),secondPos.y()) + 1; j < std::max(firstPos.y(), secondPos.y()) - 1; j++)
            if(UnitsInfo::unitsAtField[firstPos.x()][j] != nullptr)
                return false;

        return true;
}

Unit *Utils::setNewUnit(int chosen)
{
    if(chosen == 0)
        return new Queen (Chess::x, Chess::y, Pawn::forPromotion->colorBlack);
    if(chosen == 1)
        return new Bishop(Chess::x, Chess::y, Pawn::forPromotion->colorBlack);
    if(chosen == 2)
        return new Horse (Chess::x, Chess::y, Pawn::forPromotion->colorBlack);
    if(chosen == 3)
        return new Rook  (Chess::x, Chess::y, Pawn::forPromotion->colorBlack);
    return nullptr;
}

QVector<QVector<QRect> > Utils::validMove(QVector<QVector<QPoint> > allMoves)
{
    QVector<QVector<QRect>> validMoves;
    QVector<QRect> combination;

    if(allMoves.size() != 0)
    {
        for(int i = 0; i < allMoves.size(); i++)
        {
            for(int j = 0; j < allMoves[i].size(); j++)
            {
                if( (allMoves[i][j].x() >= 0 && allMoves[i][j].x() < 8) && (allMoves[i][j].y() >= 0 && allMoves[i][j].y() < 8))
                {
                    if(UnitsInfo::unitsAtField[allMoves[i][j].x()][allMoves[i][j].y()] == nullptr)
                    {
                        combination.push_back(PaintBoard::gameField[allMoves[i][j].x()][allMoves[i][j].y()]);
                    }
                    else if(UnitsInfo::unitsAtField[allMoves[i][j].x()][allMoves[i][j].y()]->colorBlack != Chess::whosTurn)
                    {
                        combination.push_back(PaintBoard::gameField[allMoves[i][j].x()][allMoves[i][j].y()]);
                        break;
                    }
                    else break;
                }
            }
            validMoves.push_back(combination);
            combination.clear();
        }
        return validMoves;
    }
    return validMoves;
}

