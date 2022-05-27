#ifndef CHESS_H
#define CHESS_H

#include "unitsinfo.h"
#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class Chess : public QWidget
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

    static Unit* currentUnit;
    static Unit *getNewUnit();
    static bool whosTurn;
    static Chess *thatOne;
    static int x;
    static int y;
    static int mouseX;
    static int mouseY;
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;


};
#endif // CHESS_H
