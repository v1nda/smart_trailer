#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>
#include "queue.h"

#define SCREEN_NUMBER 3
#define SCREEN_MAIN_ID 0
#define SCREEN_LIGHT_ID 1
#define SCREEN_STATUS_ID 2

void lcd_preinit();
void lcd_init_print(String str);
void lcd_init();

void lcd_set(queue_item &item);

#endif