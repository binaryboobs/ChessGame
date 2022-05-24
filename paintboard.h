#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "chess.h"
#include "unit.h"
#include <QtSvg>
#include <QPushButton>



class PaintBoard : public QWidget
{
public:
    PaintBoard(Chess *parent = 0);
    ~PaintBoard();
    static QVector <QVector <QRect>> gameField;
    static QVector <QVector <Unit*>> FieldUnits;

    static QVector <QVector <QRect>> moves;

    QPushButton *startGame;
    static void paintUnits(Chess *window);
    static void setGameFieldTo(Chess *window);
    static void paintGameBoard(QPaintEvent *e, Chess *window);
    static void paintMoves(Chess *window);

};
#endif // PAINTBOARD_H
