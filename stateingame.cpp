#include "stateingame.h"
#include "stateinmainmenu.h"

#include "game.h"

void StateInGame::inMainMenu(Game *game)
{
    game->setState(new StateInMainMenu());
    delete this;
}

int StateInGame::getIdState()
{
    return 1;
}
