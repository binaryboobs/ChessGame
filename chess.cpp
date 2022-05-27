#include "chess.h"
#include "paintboard.h"
#include "utils.h"
#include <QRect>
#include <QBrush>



int Chess::mouseX;
int Chess::mouseY;
Chess* Chess::thatOne;

int Chess::x;
int Chess::y;

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
    thatOne = this;
    PaintBoard::setGameFieldTo(this);
    PaintBoard::paintGameBoard(e, this);

    if(UnitsInfo::unitsAtField[mouseX][mouseY]!= nullptr && UnitsInfo::unitsAtField[mouseX][mouseY]->colorBlack == Chess::whosTurn && !Pawn::promotionAvailable)
        PaintBoard::moves = Utils::validMove(UnitsInfo::unitsAtField[mouseX][mouseY]->moves());

    PaintBoard::paintMoves(this);
    PaintBoard::paintUnits(this);

     if (Pawn::promotionAvailable)
        PaintBoard::paintPawnPromotion(this,Pawn::forPromotion);
}

void Chess::mousePressEvent(QMouseEvent *e)
{
    if(Utils::isGameArea(e->x() / PaintBoard::regularSize - 1, e->y() / PaintBoard::regularSize - 1))
    {
        Chess::mouseX = e->y() / PaintBoard::regularSize - 1;
        Chess::mouseY = e->x() / PaintBoard::regularSize - 1;
    }

    if(Pawn::promotionAvailable == false)
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
                x = currentUnit->getX(), y = currentUnit->getY();
                currentUnit = nullptr;
                PaintBoard::moves.clear();
            }
            else if (Utils::clickedAnotherUnit())
                Utils::captureUnit();
        }
    }
    if (Pawn::promotionAvailable)
    {
        if(PaintBoard::clickedChoosingWindow(e->x(),e->y()))
        {
            mouseX = e->x() / PaintBoard::regularSize - 10;

            UnitsInfo::unitsAtField[x][y]->~Unit();
            UnitsInfo::unitsAtField[x][y] = nullptr;

            currentUnit = Utils::setNewUnit(mouseX);

            currentUnit->move(QPoint(x,y));
            UnitsInfo::unitsAtField[x][y] = currentUnit;
            currentUnit = nullptr;
            Pawn::promotionAvailable = false;
        }
    }
    repaint();
}



