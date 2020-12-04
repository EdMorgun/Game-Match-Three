#ifndef CELL_H
#define CELL_H

#include "objectfigure.h"
#include "drawfigure.h"


class Figure : public ObjectFigure, public DrawFigure
{
public:
    Figure(int x, int y);
    Figure(int x, int y, QString image);
    void paintF(QPainter *painter);
    void paintMap(Figure *cells[8][8], QPainter *painter);
    void transformToBonus();
    void setZeroID();
    void setAlpha(int alpha);
    int getId();
private:
    QImage image;
    int id;
};

#endif // CELL_H
