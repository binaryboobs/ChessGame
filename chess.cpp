#include "chess.h"
#include "paintboard.h"
#include "unitsinfo.h"
#include "gamerules.h"
#include "utils.h"
#include <QRect>
#include <QBrush>
#include <QPoint>
#include <QVector>


int Chess::mouseX;
int Chess::mouseY;



Unit* Chess::currentUnit;

bool Chess::whosTurn = false;

Chess::Chess(QWidget *parent)
    : QWidget(parent)
{
    setMinimumWidth(800);
    setMinimumHeight(600);

    this->setStyleSheet("background-color:rgb(13, 13, 13);");

    QHBoxLayout *first = new QHBoxLayout;
    QHBoxLayout *second = new QHBoxLayout;
    QVBoxLayout *basic = new QVBoxLayout;

    PaintBoard a;




    first->addWidget(&a);

    basic->addLayout(second);
    basic->addLayout(first);

    UnitsInfo::initializeEmptyUnitsField();
    UnitsInfo::setUnits();
    UnitsInfo::patchUnitsToField();
    UnitsInfo::blackKing = UnitsInfo::unitsAtField[0][4];
    UnitsInfo::whiteKing = UnitsInfo::unitsAtField[7][3];

}

Chess::~Chess()
{

}

void Chess::paintEvent(QPaintEvent *e)
{
    PaintBoard::setGameFieldTo(this);
    PaintBoard::paintGameBoard(e, this);

    if(UnitsInfo::unitsAtField[mouseX][mouseY]!= nullptr && UnitsInfo::unitsAtField[mouseX][mouseY]->colorBlack == Chess::whosTurn)
        PaintBoard::moves = GameRules::validMove(UnitsInfo::unitsAtField[mouseX][mouseY]->moves());

    PaintBoard::paintMoves(this);
    PaintBoard::paintUnits(this);

}

void Chess::mousePressEvent(QMouseEvent *e)
{

    Chess::mouseX = e->y() / PaintBoard::gameField[0][0].width() - 1;
    Chess::mouseY = e->x() / PaintBoard::gameField[0][0].width() - 1;

    if(Utils::isGameArea(mouseX, mouseY))
    {
        if(Utils::firstClick())
            Utils::captureUnit();

        else if(Utils::secondClick())
        {
            bool isMove = currentUnit->isMoveOfTheUnit(PaintBoard::gameField[mouseX][mouseY]);
            if(isMove)
            {
                currentUnit->move(QPoint(mouseX,mouseY));
                whosTurn = (whosTurn + 1) % 2;
                currentUnit = nullptr;
                PaintBoard::moves.clear();
            }
            else if (Utils::clickedAnotherUnit())
                Utils::captureUnit();
        }
    }
    repaint();
}



