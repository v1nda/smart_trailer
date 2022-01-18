#include "light.h"

static bool photo;
static bool move;

void light_init()
{
        pinMode(PHOTO_PIN, INPUT);
        pinMode(PIR_PIN, INPUT);

        photo = false;
        move = false;

        return;
}

void light_sensors_renew()
{
        photo = digitalRead(PHOTO_PIN);
        photo = !photo;
        move = digitalRead(PIR_PIN);

        return;
}

queue_item light_get_photo()
{
        queue_item item;
        item.sensor_id = PHOTO_ID;
        item.value_type = VALUE_TYPE_I;
        item.value_i = photo;

        return item;
}

queue_item light_get_move()
{
        queue_item item;
        item.sensor_id = PIR_ID;
        item.value_type = VALUE_TYPE_I;
        item.value_i = move;

        return item;
}

void light_count()
{
        return;
}