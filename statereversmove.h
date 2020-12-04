#ifndef STATEREVERSMOVE_H
#define STATEREVERSMOVE_H

#include "stategamemap.h"

class StateReversMove : public StateGameMap
{
public:
    void inMove(GameMap *) override;
    int getIdState() override;
    void wait(GameMap *) override{}
    void disappear(GameMap *) override {}
    void reversMove(GameMap *) override {}
};

#endif // STATEREVERSMOVE_H
