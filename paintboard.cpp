#include <paintboard.h>
#include "chess.h"
#include "unitsinfo.h"

QVector <QVector <QRect>> PaintBoard::gameField = {};

QVector <QVector <QRect>> PaintBoard::moves = {};

PaintBoard::PaintBoard(Chess *parent)
{
    Q_UNUSED(parent);
    startGame = new QPushButton("Start Game");

    startGame->setGeometry(QRect(645,485,300,300));
}

PaintBoard::~PaintBoard()
     {
     }

void PaintBoard::setGameFieldTo(Chess *window)
{
    PaintBoard::gameField.clear();
    int scale = 10;
    int regularSize = window->width() > window->height() ? window->height() : window->width();

    QPoint rp(regularSize/scale, regularSize/scale);
    QSize  rs(regularSize/scale,regularSize/scale);

    QVector <QRect> current;
    int exmp = rp.x();

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            QRect a = QRect(rp,rs);
            current.push_back(a);
            rp.setX(rp.x()+exmp);
        }
        PaintBoard::gameField.push_back(current);
        current.clear();
        rp.setX(regularSize/scale);
        rp.setY(rp.y()+ (regularSize/scale));
    }

}

void PaintBoard::paintGameBoard(QPaintEvent *e, Chess *window)
{
    Q_UNUSED(e);

    QPainter painter;
    painter.begin(window);

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if((x+y) % 2 == 0)
                painter.setBrush(QColor(102, 51, 0));
            else
                painter.setBrush(QColor(255, 191, 128));

            painter.drawRect(PaintBoard::gameField[x][y]);
        }
    }
    painter.end();
}

void PaintBoard::paintMoves(Chess *window)
{
    QPainter painter;
    painter.begin(window);
    painter.setBrush(QColor(160,0,160));
    if(moves.size()!= 0)
    {
        for (int i = 0; i < moves.size();i++) {
            painter.drawRects(PaintBoard::moves[i]);
        }
    }
    painter.end();
}

void PaintBoard::paintUnits(Chess *window)
{
    QPainter uPainter;
    uPainter.begin(window);

    int scale = 10;
    int regularSize = window->width() > window->height() ? window->height() : window->width();

    for(int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(UnitsInfo::unitsAtField[x][y]!= nullptr)
                uPainter.drawPixmap(PaintBoard::gameField[x][y], UnitsInfo::unitsAtField[x][y]->icon.pixmap(regularSize/scale));
        }
    }

    uPainter.end();
}

