#ifndef STATEGAME_H
#define STATEGAME_H

class Game;

class StateGame
{
public:
    void virtual inMainMenu(Game *) = 0;
    void virtual inGame(Game *) = 0;
    int virtual getIdState() = 0;

    virtual ~StateGame() = default;
};

#endif // STATEGAME_H
