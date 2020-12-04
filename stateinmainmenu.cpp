#include "stateinmainmenu.h"
#include "stateingame.h"

#include "game.h"

void StateInMainMenu::inGame(Game *game)
{
    game->setState(new StateInGame());
    delete this;
}

int StateInMainMenu::getIdState()
{
    return 0;
}
