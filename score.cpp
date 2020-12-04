#include "score.h"

enum
{
    LINE = 1,
    COLORBONUS = 2
};

Score::Score()
{
    score = 0;
}

void Score::countPoints(int numberOfFigures, int formula)
{
    switch (formula)
    {
    case LINE:
        score += (numberOfFigures-2)*5*numberOfFigures;
        break;
    case COLORBONUS:
        score += numberOfFigures*10;
        break;
    }
}

void Score::setZeroScore()
{
    score = 0;
}

int Score::getScore()
{
    return score;
}
