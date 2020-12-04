#include "statedisappear.h"

#include "stateinmove.h"
#include "statewait.h"

void StateDisappear::inMove(GameMap *gm)
{
    gm->setState(new StateInMove());
    delete this;
}

void StateDisappear::wait(GameMap *gm)
{
    gm->setState(new StateWait());
    delete this;
}

int StateDisappear::getIdState()
{
    return 3;
}
