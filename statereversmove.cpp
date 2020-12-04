#include "statereversmove.h"
#include "gamemap.h"
#include "stateinmove.h"

void StateReversMove::inMove(GameMap *gm)
{
    gm->setState(new StateInMove());
    delete this;
}

int StateReversMove::getIdState()
{
    return 4;
}
