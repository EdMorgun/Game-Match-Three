#include "drawfigure.h"

#include "QDebug"

static int STANDART_SIZE = 54;

extern int SIZE;

void DrawFigure::paint(int x, int y, QPainter *painter, QImage* image)
{
    QRect r(x*SIZE/STANDART_SIZE, y*SIZE/STANDART_SIZE, SIZE, SIZE);
    painter->drawImage(r, *image);
}


