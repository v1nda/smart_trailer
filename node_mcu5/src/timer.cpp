#include "timer.h"

static long long times[TIMER_NUMBER];
static int periods[TIMER_NUMBER];

void timers_init()
{
        for (size_t i = 0; i < 4; i++)
        {
                times[i] = millis();
        }

        periods[TIMER_50MS] = 50;
        periods[TIMER_100MS] = 100;
        periods[TIMER_500MS] = 500;
        periods[TIMER_1S] = 1000;
        periods[TIMER_3S] = 3000;
        periods[TIMER_5S] = 5000;
        periods[TIMER_10S] = 10000;
}

bool is_time(int timer)
{
        bool result = false;

        if (millis() - times[timer] >= periods[timer])
        {
                result = true;
                times[timer] += periods[timer];
        }

        return result;
}