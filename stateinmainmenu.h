#ifndef STATEINMAINMENU_H
#define STATEINMAINMENU_H

#include "stategame.h"

class StateInMainMenu : public StateGame
{
public:
    void inMainMenu(Game *) override {}
    void inGame(Game *) override;

    int getIdState() override;

};

#endif // STATEINMAINMENU_H
