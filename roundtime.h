#ifndef ROUNDTIME_H
#define ROUNDTIME_H


class RoundTime
{
public:
    RoundTime(int timeMS);
    bool wasteTime();
    bool timeIsUp();
    int getTime();
private:
    int timeMS;
};

#endif // ROUNDTIME_H
