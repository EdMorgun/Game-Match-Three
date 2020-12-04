#include "statewait.h"
#include "stateinmove.h"
#include "gamemap.h"

void StateWait::inMove(GameMap *gm)
{
    gm->setState(new StateInMove());
    delete this;
}

int StateWait::getIdState()
{
    return 1;
}
