#ifndef DRAWCELL_H
#define DRAWCELL_H

#include "drawobject.h"

class DrawFigure : public DrawObject
{
public:
    void paint(int x, int y, QPainter *painter, QImage* image) override;
};

#endif // DRAWCELL_H
