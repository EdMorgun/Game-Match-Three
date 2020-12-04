#ifndef LABELESPAINTER_H
#define LABELESPAINTER_H

#include "qlabel.h"

class LabelesPainter
{
public:
    LabelesPainter(QLabel *timeLabel, QLabel *scoreLabel);
    void patntLabels(int time, int score);

private:
    void paintTime(int time);
    void paintScore(int score);
    QLabel *timeLabel, *scoreLabel;
};

#endif // LABELESPAINTER_H
