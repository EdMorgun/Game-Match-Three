#include "objectfigure.h"

enum { LEFT = 1, UP = 2, RIGHT = 3, DOWN = 4, STEP = 6 };

ObjectFigure::ObjectFigure(int x, int y) : x(x), y(y)
{

}

bool ObjectFigure::move(int x, int y)
{
    if(this->x == x && this->y == y) return false;

    if(this->x < x)
    {
        this->x += STEP;
        return true;
    }

    if(this->y < y)
    {
        this->y += STEP;
        return true;
    }

    if(this->x > x)
    {
        this->x -= STEP;
        return true;
    }

    if(this->y > y)
    {
        this->y -= STEP;
        return true;
    }
    return false;
}

void ObjectFigure::setCoordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}

int ObjectFigure::getX()
{
    return x;
}

int ObjectFigure::getY()
{
    return y;
}
