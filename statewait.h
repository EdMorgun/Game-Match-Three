#ifndef STATEWAIT_H
#define STATEWAIT_H

#include "stategamemap.h"

class StateWait : public StateGameMap
{
public:
    void inMove(GameMap *) override;

    int getIdState() override;

    void virtual reversMove(GameMap*) override {}
    void virtual disappear(GameMap *) override {}
    void virtual wait(GameMap *) override {}
};

#endif // STATEWAIT_H
