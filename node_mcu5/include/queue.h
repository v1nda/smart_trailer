#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>
#include "defines.h"

#define QUEUE_SIZE 64

#define VALUE_TYPE_I 0
#define VALUE_TYPE_F 1
#define VALUE_TYPE_S 2

struct queue_item
{
        byte board_id;
        byte sensor_id;
        byte type_id;
        byte value_type;
        int value_i;
        float value_f;
        String value_s;
};

class Queue
{
private:
        queue_item item[QUEUE_SIZE];
        int count;

public:
        Queue();
        ~Queue();

        void enqueue(queue_item new_item);
        queue_item dequeue();
        bool is_empty();
        int size();
        void print();
};

#endif