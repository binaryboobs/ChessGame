#include "gamerules.h"
#include "paintboard.h"
#include "unit.h"
#include "unitsinfo.h"
QVector <QVector<QRect>> GameRules::validMove(QVector<QVector<QPoint>> allMoves)
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





