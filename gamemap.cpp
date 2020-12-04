#include "gamemap.h"
#include "statewait.h"
#include "statedisappear.h"
#include "stateinmove.h"
#include "statereversmove.h"
#include "stdio.h"

static int STANDART_SIZE = 54;

extern int SIZE;

enum
{
    indentX = 44,
    indentY = 23,

    StateIDWait = 1,
    StateIDInMove = 2,
    StateIDDisappear = 3,
    StateIDReversMove = 4,

    alphaToDisappear = 220,

    LINE = 1,
    BONUSCOLOR = 2,
};

GameMap::GameMap(QLabel *timeLabel, QLabel *scoreLabel) : hintTimer(2000), selectedCellX1(1000), selectedCellY1(1000), selectedCellX2(0),
    selectedCellY2(0), moveChecked(false), mouseMove(false), moveBonus(false), timeLabel(timeLabel), scoreLabel(scoreLabel)
{
    cursor.load(":/Images/cursor.png");
    hint1 = new Figure(0, 0, ":/Images/hint.png");
    hint2 = new Figure(0, 0, ":/Images/hint.png");
    score = new Score();

    loadMap();

    score->setZeroScore();

    timer = new RoundTime(30000);

    this->state = new StateInMove();
}

void GameMap::loadMap()
{
    for(int raw = 0; raw < 8; raw++)
        for(int colon = 0; colon < 8; colon++)
            cells[raw][colon] = new Figure(indentX + STANDART_SIZE*colon,
                                           indentY + STANDART_SIZE*raw-STANDART_SIZE*10);      

    if(checkThreeInMatch())
    {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                delete cells[i][j];

        disappearList.clear();
        bonusList.clear();

        loadMap();
    }
}

void GameMap::setState(StateGameMap *s)
{
    this->state = s;
}

void GameMap::paint(QPainter *painter)
{
    paintMap(painter);
}

void GameMap::paintMap(QPainter *painter)
{
    cells[0][0]->paintMap(cells, painter);
    for(int raw = 0; raw < 8; raw++)
        for(int colon = 0; colon < 8; colon++)
        {
            if(selectedCellX1 == colon && selectedCellY1 == raw && state->getIdState() == StateIDWait)
            {
                cells[raw][colon]->paintF(painter);
            }
            if(state->getIdState() == StateIDWait && hintTimer < 0)
            {
                hint1->paintF(painter);
                hint2->paintF(painter);
            }
        }
}

bool GameMap::checkThreeInMatch()
{
    bool threeInMatch(false);
    int currentId, countFigures;

    for(int raw = 0; raw < 8; raw++)
    {
        countFigures = 0;
        currentId = cells[raw][0]->getId();

        for(int colon = 0; colon < 8; colon++)
        {
            if(cells[raw][colon]->getId() == currentId) countFigures++;
            if(!(cells[raw][colon]->getId() == currentId))
            {
                if(countFigures >= 3)
                {
                    score->countPoints(countFigures, LINE);
                    if(countFigures == 5) bonusList.push_back(cells[raw][colon-2]);
                    for(int i = 0; i < countFigures; i++) disappearList.push_back(cells[raw][colon-i-1]);
                    threeInMatch =true;
                }
                countFigures = 1;
                currentId = cells[raw][colon]->getId();
            }
            if(colon == 7)
                if(countFigures >= 3)
                {
                    score->countPoints(countFigures, LINE);
                    if(countFigures == 5) bonusList.push_back(cells[raw][colon-2]);
                    for(int i = 0; i < countFigures; i++) disappearList.push_back(cells[raw][colon-i]);
                    threeInMatch =true;
                }
        }
    }

    for(int colon = 0; colon < 8; colon++)
    {
        countFigures = 0;
        currentId = cells[0][colon]->getId();
        for(int raw = 0; raw < 8; raw++)
        {
            if(cells[raw][colon]->getId() == currentId) countFigures++;
            if(!(cells[raw][colon]->getId() == currentId))
            {
                if(countFigures >= 3)
                {
                    score->countPoints(countFigures, LINE);
                    if(countFigures == 5) bonusList.push_back(cells[raw-2][colon]);
                    for(int i = 0; i < countFigures; i++) disappearList.push_back(cells[raw-i-1][colon]);
                    threeInMatch =true;
                }
                countFigures = 1;
                currentId = cells[raw][colon]->getId();
            }
            if(raw == 7)
                if(countFigures >= 3)
                {
                    score->countPoints(countFigures, LINE);
                    if(countFigures == 5) bonusList.push_back(cells[raw-2][colon]);
                    for(int i = 0; i < countFigures; i++) disappearList.push_back(cells[raw-i][colon]);
                    threeInMatch =true;
                }
        }
    }

    return threeInMatch;
}



void GameMap::checkMove()
{
    for(int raw = 0; raw < 8; raw++)
    {
        if(moveChecked) break;
        for(int colon = 0; colon < 8; colon++)
        {
            if(moveChecked) break;
            for(int mask = 1; mask <= 16; mask++)
            {
               if(moveChecked) break;
               if(raw <= 5 && colon <= 6 && mask <= 6)
               {
                   moveChecked = checkSearchMask(colon, raw, mask);
                   continue;
               }
               if(colon <= 5 && raw <= 6 && mask >= 7 && mask <= 12)
               {
                   moveChecked = checkSearchMask(colon, raw, mask);
                   continue;
               }
               if(colon <= 4 && mask >= 15)
               {
                   moveChecked = checkSearchMask(colon, raw, mask);
                   continue;
               }
               if(raw <= 4 && (mask == 13 || mask == 14))
               {
                   moveChecked = checkSearchMask(colon, raw, mask);
                   continue;
               }
            }
        }
    }
}

bool GameMap::checkSearchMask(int x, int y, int mask)
{
    switch (mask)
    {
    case 1:
        if(cells[y][x]->getId() == cells[y+1][x]->getId() &&
                cells[y+1][x]->getId() == cells[y+2][x+1]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*x + indentX,STANDART_SIZE*(y+2) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+1) + indentX, STANDART_SIZE*(y+2) + indentY);
            return true;
        }
        break;
    case 2:
        if(cells[y][x+1]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y+2][x]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*x + indentX,STANDART_SIZE*(y+2) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+1) + indentX, STANDART_SIZE*(y+2) + indentY);
            return true;
        }
        break;
    case 3:
        if(cells[y][x]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y+2][x]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y+1) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 4:
        if(cells[y][x+1]->getId() == cells[y+1][x]->getId() &&
                cells[y+1][x]->getId() == cells[y+2][x]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y) + indentY);
            return true;
        }
        break;
    case 5:
        if(cells[y][x]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y+2][x+1]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y) + indentY);
            return true;
        }
        break;
    case 6:
        if(cells[y][x+1]->getId() == cells[y+1][x]->getId() &&
                cells[y+1][x]->getId() == cells[y+2][x+1]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y+1) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 7:
        if(cells[y+1][x]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+2) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+2) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 8:
        if(cells[y][x]->getId() == cells[y][x+1]->getId() &&
                cells[y][x+1]->getId() == cells[y+1][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+2) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+2) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 9:
        if(cells[y][x]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y+1][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 10:
        if(cells[y+1][x]->getId() == cells[y][x+1]->getId() &&
                cells[y][x+1]->getId() == cells[y][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 11:
        if(cells[y+1][x]->getId() == cells[y][x+1]->getId() &&
                cells[y][x+1]->getId() == cells[y+1][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+1) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 12:
        if(cells[y][x]->getId() == cells[y+1][x+1]->getId() &&
                cells[y+1][x+1]->getId() == cells[y][x+2]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+1) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+1) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 13:
        if(cells[y][x]->getId() == cells[y+1][x]->getId() &&
                cells[y+1][x]->getId() == cells[y+3][x]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x) + indentX,STANDART_SIZE*(y+2) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+3) + indentY);
            return true;
        }
        break;
    case 14:
        if(cells[y][x]->getId() == cells[y+2][x]->getId() &&
                cells[y+2][x]->getId()  == cells[y+3][x]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x) + indentX, STANDART_SIZE*(y+1) + indentY);
            return true;
        }
        break;
    case 15:
        if(cells[y][x]->getId() == cells[y][x+1]->getId() &&
                cells[y][x+1]->getId()  == cells[y][x+3]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x+2) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+3) + indentX, STANDART_SIZE*(y) + indentY);
            return true;
        }
        break;
    case 16:
        if(cells[y][x]->getId() == cells[y][x+2]->getId() &&
                cells[y][x+2]->getId() == cells[y][x+3]->getId())
        {
            hint1->setCoordinates(STANDART_SIZE*(x) + indentX,STANDART_SIZE*(y) + indentY);
            hint2->setCoordinates(STANDART_SIZE*(x+1) + indentX, STANDART_SIZE*(y) + indentY);
            return true;
        }
        break;
    }
    return false;
}

bool GameMap::checkNeighbors(int mouseCellX, int mouseCellY)
{
    if(mouseCellX > 7 || mouseCellY > 7) return false;
    if((abs(mouseCellX - selectedCellX1) + abs(mouseCellY - selectedCellY1)) == 1)
    {
        selectedCellX2 = mouseCellX;
        selectedCellY2 = mouseCellY;
        return true;
    }
    else
    {
        selectedCellX1 = mouseCellX;
        selectedCellY1 = mouseCellY;
        return false;
    }
}

void GameMap::replenishCells()
{
    int zeroCount;
    for(int colon = 0; colon < 8; colon++)
    {
        zeroCount = 0;
        for(int raw = 0; raw < 8; raw++)
        {
            if(cells[raw][colon]->getId() == 0)
            {
                zeroCount++;
            }
        }
        for(int i = 0; i < zeroCount; i++)
        {
            delete cells[(zeroCount-i-1)][colon];
            cells[zeroCount-i-1][colon] = new Figure(indentX + STANDART_SIZE*colon, indentY - STANDART_SIZE*(1+i));
        }
    }
}

void GameMap::changeLocation()
{
    for(int colon = 0; colon < 8; colon++)
    {
        for(int raw = 7; raw >= 0; raw--)
        {
            if(cells[raw][colon]->getId() == 0 && raw != 0)
            {
                for(int i = raw-1; i >= 0; i--)
                {
                    if(cells[i][colon]->getId() != 0)
                    {
                        swap(raw, colon, i, colon);
                        break;
                    }
                }
            }
        }
    }

    replenishCells();
}

void GameMap::mouseMoveEvent(QMouseEvent *e)
{
    if(state->getIdState() == StateIDWait)
    {
        if((e->x() >= indentX && e->x() <= indentX + 8*STANDART_SIZE) &&
                (e->y() >= indentY && e->y() <= indentY + 8*STANDART_SIZE))
        {
            if((e->x()*SIZE/STANDART_SIZE - indentX) / STANDART_SIZE != selectedCellX1 ||
               (e->y()*SIZE/STANDART_SIZE - indentY) / STANDART_SIZE != selectedCellY1)
            {
                if(checkNeighbors((e->x()*SIZE/STANDART_SIZE - indentX) / STANDART_SIZE,
                                  (e->y()*SIZE/STANDART_SIZE - indentY) / STANDART_SIZE))
                {
                    swap(selectedCellY1, selectedCellX1, selectedCellY2, selectedCellX2);
                    if(cells[selectedCellY1][selectedCellX1]->getId() == 7 ||
                            cells[selectedCellY2][selectedCellX2]->getId() == 7)
                        moveBonus = true;

                    mouseMove = true;
                    inMove();
                }
            }
        }
    }
}

void GameMap::swap(int raw1, int colon1, int raw2, int colon2)
{
    Figure* reserveFigure = cells[raw1][colon1];
    cells[raw1][colon1] = cells[raw2][colon2];
    cells[raw2][colon2] = reserveFigure;
}

void GameMap::useBonus(int y1, int x1, int y2, int x2)
{
    int idForDestoyed;
    if(cells[y1][x1]->getId() == 7)
    {
        idForDestoyed = cells[y2][x2]->getId();
        disappearList.push_back(cells[y1][x1]);
    }
    else
    {
        idForDestoyed = cells[y1][x1]->getId();
        disappearList.push_back(cells[y2][x2]);
    }


    for(int raw = 0; raw < 8; raw++)
        for(int colon = 0; colon < 8; colon++)
            if(cells[raw][colon]->getId() == idForDestoyed)
                disappearList.push_back(cells[raw][colon]);

    score->countPoints(static_cast<int>(disappearList.size()), BONUSCOLOR);

    disappear();
}

bool GameMap::move()
{
    bool move(false);

    for(int raw = 0; raw < 8; raw++)
        for(int colon = 0; colon < 8; colon++)
            if(!move) move = cells[raw][colon]->move(indentX + colon*STANDART_SIZE, indentY + raw*STANDART_SIZE);
                else cells[raw][colon]->move(indentX + colon*STANDART_SIZE, indentY + raw*STANDART_SIZE);

    return move;
}

bool GameMap::disappearing()
{
    alpha -= 1;
    if(alpha >= alphaToDisappear)
    {
        for(std::vector<Figure*>::iterator figure = disappearList.begin(); figure < disappearList.end(); figure++)
            (*figure)->setAlpha(alpha);

        return false;
    }
    else
    {
        for(std::vector<Figure*>::iterator figure = disappearList.begin(); figure < disappearList.end(); figure++)
            (*figure)->setZeroID();

        disappearList.clear();

        for(std::vector<Figure*>::iterator figure = bonusList.begin(); figure < bonusList.end(); figure++)
            (*figure)->transformToBonus();

        bonusList.clear();

        return true;
    }
}

void GameMap::frame()
{
    switch (state->getIdState())
    {
    case StateIDWait:
        hintTimer -= 17;
        timer->wasteTime();
        break;
    case StateIDInMove:
        if(!move()) moveBonus ? useBonus(selectedCellY1, selectedCellX1, selectedCellY2, selectedCellX2) :
                                checkThreeInMatch() ? disappear() : mouseMove ? reversMove() : wait();
        break;
    case StateIDDisappear:
        if(disappearing())
        {
            changeLocation();
            inMove();
        }
        break;
    case StateIDReversMove:
        swap(selectedCellY2, selectedCellX2, selectedCellY1, selectedCellX1);
        inMove();
        break;
    }
}

void GameMap::wait()
{
    selectedCellX1 = 100;
    selectedCellX2 = 100;
    selectedCellY1 = 50;
    selectedCellY2 = 50;

    hintTimer = 2000;
    moveChecked = false;
    checkMove();

    state->wait(this);
}

void GameMap::inMove()
{
    state->inMove(this);
}

void GameMap::reversMove()
{
    mouseMove = false;
    state->reversMove(this);
}

void GameMap::disappear()
{
    moveBonus = false;
    mouseMove = false;
    alpha = 255;
    state->disappear(this);
}

int GameMap::getTime()
{
    return timer->getTime();
}

int GameMap::getScore()
{
    return score->getScore();
}

GameMap::~GameMap()
{
    for(std::vector<Figure*>::iterator figure = disappearList.begin(); figure < disappearList.end(); figure++)
        disappearList.erase(figure);
    for(std::vector<Figure*>::iterator figure = bonusList.begin(); figure < bonusList.end(); figure++)
        bonusList.erase(figure);

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            delete cells[i][j];

    delete hint1;
    delete hint2;
    delete state;
    delete timer;
    delete score;
}
