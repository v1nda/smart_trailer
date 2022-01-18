#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "queue.h"

#define BUTTON_SLEEP_TIME 500

void button_init();
void button_renew();
bool is_tap();
queue_item button_get_item(byte index);
bool button_wake_up();

#endif