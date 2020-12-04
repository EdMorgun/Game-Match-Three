#ifndef STATEDISAPPEAR_H
#define STATEDISAPPEAR_H

#include "gamemap.h"
#include "stategamemap.h"

class StateDisappear : public StateGameMap
{
public:
    void inMove(GameMap *) override;
    void wait(GameMap *) override;
    int getIdState() override;

    void disappear(GameMap *) override {}
    void reversMove(GameMap *) override {}
};

#endif // STATEDISAPPEAR_H
