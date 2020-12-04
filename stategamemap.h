#ifndef STATEGAMEMAP_H
#define STATEGAMEMAP_H

class GameMap;

class StateGameMap
{
public:
    void virtual inMove(GameMap *) = 0;
    void virtual wait(GameMap *) = 0;
    void virtual reversMove(GameMap*) = 0;
    void virtual disappear(GameMap *) = 0;
    int virtual getIdState() = 0;

    virtual ~StateGameMap() = default;
};

#endif // STATEGAMEMAP_H
