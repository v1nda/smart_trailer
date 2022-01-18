#include "relay.h"

static bool relay_status;
static bool relay_locked;

void relay_init()
{
        pinMode(RELAY1_PIN, OUTPUT);
        relay_status = false;
        relay_locked = false;
        
        digitalWrite(RELAY1_PIN, HIGH);

        return;
}

void relay_set(bool value)
{
        if (value && !relay_locked && !relay_status)
        {
                digitalWrite(RELAY1_PIN, LOW);
                relay_status = true;
        }
        else if (!value && !relay_locked && relay_status)
        {
                digitalWrite(RELAY1_PIN, HIGH);
                relay_status = false;
        }

        return;
}

void relay_lock()
{
        if (!relay_locked)
        {
                relay_set(false);
                relay_locked = true;
        }

        return;
}

void relay_unlock()
{
        if (relay_locked)
        {
                relay_locked = false;
        }

        return;
}
