#include "labelespainter.h"

LabelesPainter::LabelesPainter(QLabel *timeLabel, QLabel *scoreLabel) : timeLabel(timeLabel), scoreLabel(scoreLabel)
{

}

void LabelesPainter::patntLabels(int time, int score)
{
    paintTime(time);
    paintScore(score);
}

void LabelesPainter::paintTime(int time)
{
    int min = time / 60000;
    int tenSec = (time - min*60000) / 10000;
    int sec = (time - min*60000 - tenSec*10000) / 1000;
    timeLabel->setText(("Time: " + std::to_string(min) + ":"
                        + std::to_string(tenSec) + std::to_string(sec)).c_str());
}

void LabelesPainter::paintScore(int score)
{
    scoreLabel->setText(("Score: " + std::to_string(score)).c_str());
}
