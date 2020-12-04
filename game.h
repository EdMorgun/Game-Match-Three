#ifndef GAME_H
#define GAME_H

#include "gamemap.h"
#include "stategame.h"

#include "QMouseEvent"
#include "QPushButton"
#include "QLabel"
#include "qlineedit.h"
#include "recordtable.h"
#include "map"
#include "labelespainter.h"

class Game
{
public:
    Game(QLabel *timeLabel, QLabel *scoreLabel, QLineEdit *lineEdit, QPushButton *button);
    void setState(StateGame *s);
    void mouseMoveEvent(QMouseEvent *e);
    void pressButton();
    void paint(QPainter *painter);
    QImage getImageSymbol(char ch);
    void paintRecordTable(QPainter *painter);

    void checkTimeUp();
    void frame();
    void inGame();
    void inMainMenu();

    ~Game();

private:
    LabelesPainter *LP;
    std::multimap<int, std::string> *records;
    RecordTable *recordTable;
    GameMap *map;
    StateGame *state;
    QLabel *timeLabel, *scoreLabel;
    QLineEdit *lineEdit;
    QPushButton *button;
    QImage alphabet;
};

#endif // GAME_H
