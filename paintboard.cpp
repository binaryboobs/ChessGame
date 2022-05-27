#include "paintboard.h"
#include <QPair>

QVector <QVector <QRect>> PaintBoard::gameField = {};

QVector <QVector <QRect>> PaintBoard::moves = {};

int PaintBoard::regularSize;

PaintBoard::PaintBoard(Chess *parent)
{
    Q_UNUSED(parent);
}

PaintBoard::~PaintBoard()
{
}

void PaintBoard::paintPawnPromotion(Chess* window, Unit* pawn)
{

    Pawn::promoteTo[0].first = QRect       (gameField[0][7].x() + regularSize*2, gameField[0][7].y(), regularSize, regularSize);
    Pawn::promoteTo[1].first = QRect(Pawn::promoteTo[0].first.x() + regularSize, gameField[0][7].y(), regularSize, regularSize);
    Pawn::promoteTo[2].first = QRect(Pawn::promoteTo[1].first.x() + regularSize, gameField[0][7].y(), regularSize, regularSize);
    Pawn::promoteTo[3].first = QRect(Pawn::promoteTo[2].first.x() + regularSize, gameField[0][7].y(), regularSize, regularSize);

    Pawn::promoteTo[0].second = pawn->colorBlack ? QIcon(":/icons/qb.svg") : QIcon(":/icons/qw.svg");
    Pawn::promoteTo[1].second = pawn->colorBlack ? QIcon(":/icons/bb.svg") : QIcon(":/icons/bw.svg");
    Pawn::promoteTo[2].second = pawn->colorBlack ? QIcon(":/icons/nb.svg") : QIcon(":/icons/nw.svg");
    Pawn::promoteTo[3].second = pawn->colorBlack ? QIcon(":/icons/rb.svg") : QIcon(":/icons/rw.svg");

    QPainter painter;
    painter.begin(window);
    painter.setBrush(QColor(80,80,80));
    for(int i = 0; i < 4; i++)
    {
        painter.drawRect(Pawn::promoteTo[i].first);
        painter.drawPixmap(Pawn::promoteTo[i].first, Pawn::promoteTo[i].second.pixmap(regularSize));
    }
    painter.end();
}

void PaintBoard::setGameFieldTo(Chess *window)
{
    PaintBoard::gameField.clear();

    regularSize = (window->width() > window->height() ? window->height() : window->width()) / 10;

    QPoint rp(regularSize, regularSize);
    QSize  rs(regularSize, regularSize);

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
        rp.setX(regularSize);
        rp.setY(rp.y()+ (regularSize));
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
        for (int i = 0; i < moves.size();i++)
            painter.drawRects(PaintBoard::moves[i]);

    painter.end();
}

bool PaintBoard::clickedChoosingWindow(int x, int y)
{
    return (x > Pawn::promoteTo[0].first.x()                           && y > Pawn::promoteTo[3].first.y()) &&
           (x < Pawn::promoteTo[3].first.x() + PaintBoard::regularSize && y < Pawn::promoteTo[3].first.y() + PaintBoard::regularSize);
}

void PaintBoard::paintUnits(Chess *window)
{
    QPainter uPainter;
    uPainter.begin(window);

    regularSize = (window->width() > window->height() ? window->height() : window->width()) / 10;

    for(int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            if(UnitsInfo::unitsAtField[x][y]!= nullptr)
                uPainter.drawPixmap(PaintBoard::gameField[x][y], UnitsInfo::unitsAtField[x][y]->icon.pixmap(regularSize));

    uPainter.end();
}

