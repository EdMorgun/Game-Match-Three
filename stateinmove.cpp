#include "stateinmove.h"

#include "statewait.h"
#include "statedisappear.h"
#include "statereversmove.h"

void StateInMove::wait(GameMap *gm)
{
    gm->setState(new StateWait());
    delete this;
}

void StateInMove::disappear(GameMap *gm)
{
    gm->setState(new StateDisappear());
    delete this;
}

void StateInMove::reversMove(GameMap *gm)
{
    gm->setState(new StateReversMove());
    delete this;
}

int StateInMove::getIdState()
{
    return 2;
}
