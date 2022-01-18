#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

#define TIMER_NUMBER 7
#define TIMER_50MS 0
#define TIMER_100MS 1
#define TIMER_500MS 2
#define TIMER_1S 3
#define TIMER_3S 4
#define TIMER_5S 5
#define TIMER_10S 6

void timers_init();
bool is_time(int period);

#endif