#ifndef OBJECTCELL_H
#define OBJECTCELL_H

#include "objectphysical.h"

class ObjectFigure : public ObjectPhysical
{
public:
    ObjectFigure(int x, int y);
    bool move(int x, int y) override final;
    void setCoordinates(int x, int y);
    int getX();
    int getY();

protected:
    int x, y, vector;

};

#endif // OBJECTCELL_H
