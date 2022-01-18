#include "button.h"

static bool button_status[BUTTON_NUMBER];
static int button_timer;
static bool tap;

void button_init()
{
        pinMode(BUTTON1_PIN, INPUT);
        pinMode(BUTTON2_PIN, INPUT);

        button_timer = millis();
        tap = false;
        for (int i = 0; i < BUTTON_NUMBER; i++)
        {
                button_status[i] = false;
        }

        return;
}

void button_renew()
{
        button_status[BUTTON1_ID - BUTTON_ID_SUB] = digitalRead(BUTTON1_PIN);
        button_status[BUTTON2_ID - BUTTON_ID_SUB] = digitalRead(BUTTON2_PIN);
        for (int i = 0; i < BUTTON_NUMBER; i++)
        {
                if (button_status[i])
                {
                        tap = true;
                }
        }

        return;
}

bool is_tap()
{
        return tap;
}

queue_item button_get_item(byte index)
{
        queue_item item;
        item.sensor_id = index;
        item.value_type = VALUE_TYPE_I;
        item.value_i = button_status[index - BUTTON_ID_SUB];

        button_status[index - BUTTON_ID_SUB] = false;
        button_timer = millis();
        tap = false;

        return item;
}

bool button_wake_up()
{
        if (millis() - button_timer > BUTTON_SLEEP_TIME)
        {
                return true;
        }

        return false;
}
