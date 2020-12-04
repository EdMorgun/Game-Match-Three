#ifndef STATEINGAME_H
#define STATEINGAME_H

#include "stategame.h"

class StateInGame : public StateGame
{
public:
    void inMainMenu(Game *) override;
    int getIdState() override;
    void inGame(Game *) override {}
};

#endif // STATEINGAME_H
