#ifndef OBJECTPHYSICAL_H
#define OBJECTPHYSICAL_H

class ObjectPhysical
{
public:
    bool virtual move(int x, int y) = 0;
    virtual ~ObjectPhysical() = default;
};

#endif // OBJECTPHYSICAL_H
