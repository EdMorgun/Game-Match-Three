#include "roundtime.h"

RoundTime::RoundTime(int timeMS) : timeMS(timeMS)
{

}

bool RoundTime::wasteTime()
{
    timeMS -= 17;
    return timeIsUp();
}

bool RoundTime::timeIsUp()
{
    if(timeMS <= 0)
    {
        timeMS = 0;
        return true;
    }
    return false;
}

int RoundTime::getTime()
{
    return timeMS;
}
