#include "queue.h"

Queue::Queue()
{
        count = 0;

        return;
}

Queue::~Queue()
{
        return;
}

void Queue::enqueue(queue_item new_item)
{
        if (count == QUEUE_SIZE)
        {
                dequeue();
        }

        item[count].board_id = THIS_BOARD_ID;
        item[count].sensor_id = new_item.sensor_id;
        item[count].type_id = new_item.type_id;
        item[count].value_type = new_item.value_type;
        item[count].value_i = new_item.value_i;
        item[count].value_f = new_item.value_f;
        item[count].value_s = new_item.value_s;
        this->count++;

        return;
}

queue_item Queue::dequeue()
{
        queue_item item_temp;
        if (count == 0)
        {
                return item_temp;
        }

        item_temp = item[0];
        count--;

        for (int i = 0; i < count; i++)
        {
                item[i] = item[i + 1];
        }

        return item_temp;
}

bool Queue::is_empty()
{
        return count == 0;
}

int Queue::size()
{
        return count;
}

void Queue::print()
{
        for (int i = 0; i < count; i++)
        {
                Serial.print(item[i].sensor_id);
                Serial.print(" ");
                Serial.print(item[i].type_id);
                Serial.print(" ");
                Serial.print(item[i].value_type);
                Serial.print(" ");
                Serial.print(item[i].value_i);
                Serial.print(" ");
                Serial.println(item[i].value_f);
        }

        return;
}