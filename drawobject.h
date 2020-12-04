#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include "QPainter"

class DrawObject
{
public:
    void virtual paint(int x, int y, QPainter *painter, QImage* image) = 0;
    virtual ~DrawObject() = default;
};

#endif // DRAWOBJECT_H
