#ifndef STATEINMOVE_H
#define STATEINMOVE_H

#include "stategamemap.h"

class StateInMove : public StateGameMap
{
public:
    void wait(GameMap *) override;
    void disappear(GameMap *) override;
    void reversMove(GameMap *) override;

    int getIdState() override;

    void inMove(GameMap *) override {}
};

#endif // STATEINMOVE_H
