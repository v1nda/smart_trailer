#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "queue.h"

void light_init();
void light_sensors_renew();
queue_item light_get_photo();
queue_item light_get_move();

void light_count();

#endif