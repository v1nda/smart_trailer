#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "queue.h"

void relay_init();
void relay_set(bool value);

void relay_lock();
void relay_unlock();

#endif