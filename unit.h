#ifndef UNIT_H
#define UNIT_H

#include <QVector>
#include <QSvgWidget>
#include <QPoint>
#include <QIcon>

class Unit
{
public:

    int x;
    int y;
    bool colorBlack;
    bool unmoved;
    QIcon icon;
    void construct(int x, int y, bool isBlack);

    int getX();
    int getY();

    bool isMoveOfTheUnit(QRect &cell);

    virtual QVector <QVector <QPoint>> moves();
    virtual void move(QPoint cell);
    virtual ~Unit();
};

class Queen : public Unit
{
public:
    Queen(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
};

class King : public Unit
{
public:
    King(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
    void move(QPoint cell) override;
    void goRooking();
    QVector <QPoint> findRookingSpots();
};

class Bishop : public Unit
{
public:
    Bishop(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
};

class Rook : public Unit
{
public:
    Rook(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
};

class Horse : public Unit
{
public:
    Horse(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
};

class Pawn : public Unit
{
public:

    Pawn(int xPos, int yPos, bool isBlack);
    QVector <QVector <QPoint>> moves() override;
    void move(QPoint cell) override;
    int direction;
    bool isEnPassantMove();
    void setEnPassantPos();
    void doEnPassant();
    void includeEnPassantPos(QVector<QVector<QPoint>> &moves);
};

#endif // UNIT_H
