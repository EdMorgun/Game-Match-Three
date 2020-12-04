#ifndef MAP_H
#define MAP_H

#include "figure.h"
#include "drawfigure.h"
#include "stategamemap.h"
#include "vector"
#include "QMouseEvent"
#include "roundtime.h"
#include "QLabel"
#include "score.h"

class GameMap
{
public:
    GameMap(QLabel *timeLabel, QLabel *scoreLabel);
    void loadMap();
    void setState(StateGameMap *s);

    void paint(QPainter *painter);
    void paintMap(QPainter *painter);

    bool checkThreeInMatch();
    void checkMove();
    bool checkSearchMask(int x, int y, int mask);
    bool checkNeighbors(int mouseClickX, int mouseClickY);

    void replenishCells();
    void changeLocation();

    void mouseMoveEvent(QMouseEvent *e);
    void swap(int raw1, int colon1, int raw2, int colon2);
    void useBonus(int y1, int x1, int y2, int x2);
    bool move();
    bool disappearing();

    void frame();

    void wait();
    void inMove();
    void reversMove();
    void disappear();

    int getTime();
    int getScore();

    ~GameMap();

private:
    std::vector<Figure*> bonusList;
    std::vector<Figure*> disappearList;
    Figure* cells[8][8];
    Figure* hint1;
    Figure* hint2;

    RoundTime *timer;
    Score *score;
    StateGameMap *state;

    int alpha, hintTimer, selectedCellX1, selectedCellY1, selectedCellX2, selectedCellY2;
    bool moveChecked, mouseMove, moveBonus;

    QLabel *timeLabel, *scoreLabel;
    QRect updateRect;
    QImage cursor;
};

#endif // MAP_H
