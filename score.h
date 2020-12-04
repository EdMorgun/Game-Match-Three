#ifndef SCORE_H
#define SCORE_H


class Score
{
public:
    Score();
    void countPoints(int numberOfFigures, int formula);
    void setZeroScore();
    int getScore();
private:
    int score;
};

#endif // SCORE_H
