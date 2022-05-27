#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "chess.h"
#include "unitsinfo.h"
#include <QtSvg>



class PaintBoard : public QWidget
{
public:
    PaintBoard(Chess *parent = 0);
    ~PaintBoard();

    static QVector <QVector <QRect>> gameField;
    static int regularSize;
    static QVector <QVector <QRect>> moves;
    static void paintPawnPromotion(Chess* window, Unit* paw);
    static void paintUnits(Chess *window);
    static void setGameFieldTo(Chess *window);
    static void paintGameBoard(QPaintEvent *e, Chess *window);
    static void paintMoves(Chess *window);
    static bool clickedChoosingWindow(int x, int y);


};
#endif // PAINTBOARD_H
