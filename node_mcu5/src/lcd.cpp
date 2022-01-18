#include "lcd.h"

static LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4);

static int init_str_num = 0;
static String screens[SCREEN_NUMBER][4] = {
{
        "       C | Climate  ",
        "       % |          ",
        "      mm |         C",
        "                    "
},
{
        "> test screen       ",
        "                    ",
        "                    ",
        "                    "
},
{
        "WiFi>               ",
        "MQTT>               ",
        "                    ",
        "                    "
}
};

static byte current_screen;

// Local functions

void print_screen(byte index)
{
        lcd.clear();
        for (int i = 0; i < 4; i++)
        {
                lcd.setCursor(0, i);
                lcd.print(screens[index][i]);
        }
        current_screen = index;

        return;
}

void set_to_screen(byte screen, byte x, byte y, String str)
{
        for (unsigned int i = 0; i < str.length(); i++)
        {
                screens[screen][y][x] = str[i];

                if (current_screen == screen)
                {
                        lcd.setCursor(x, y);
                        lcd.print(F(" "));
                        lcd.setCursor(x, y);
                        lcd.print(str[i]);
                }
                x++;
        }

        return;
}

// Global functions

void lcd_preinit()
{
        lcd.init();
        lcd.backlight();
        lcd.clear();

        lcd.setCursor(0, init_str_num);
        lcd.print(F("Initialization ..."));
        lcd.setCursor(0, ++init_str_num);
        lcd.print(F("["));
        lcd.setCursor(19, init_str_num);
        lcd.print(F("]"));
        for (int i = 1; i < 19; i++)
        {
                lcd.setCursor(i, init_str_num);
                lcd.print(F("="));
                delay(300);
        }

        return;
}

void lcd_init_print(String str)
{
        lcd.setCursor(0, ++init_str_num);
        lcd.print(str);
}

void lcd_init()
{
        lcd.clear();

        print_screen(SCREEN_MAIN_ID);

        return;
}

void lcd_set(queue_item &item)
{
        if (item.sensor_id == BME_ID)
        {
                if (item.type_id == TYPE_TEMP)
                {
                        set_to_screen(SCREEN_MAIN_ID, 0, 0, String(item.value_f));
                }
                else if (item.type_id == TYPE_HUM)
                {
                        set_to_screen(SCREEN_MAIN_ID, 0, 1, String(item.value_f));
                }
                else if (item.type_id == TYPE_PRES)
                {
                        set_to_screen(SCREEN_MAIN_ID, 0, 2, String(item.value_f));
                }
        }
        else if(item.sensor_id == WIFI_ID || item.sensor_id == MQTT_ID)
        {
                if(item.sensor_id == WIFI_ID)
                {
                        if (item.value_i == 1)
                        {
                                set_to_screen(SCREEN_STATUS_ID, 6, 0, "ok   ");
                        }
                        else
                        {
                                set_to_screen(SCREEN_STATUS_ID, 6, 0, "error");
                        }
                }
                else if(item.sensor_id == MQTT_ID)
                {
                        if (item.value_i == MQTT_CONNECTION_ON)
                        {
                                set_to_screen(SCREEN_STATUS_ID, 6, 1, "ok        ");
                        }
                        else if (item.value_i == MQTT_CONNECTION_OFF)
                        {
                                set_to_screen(SCREEN_STATUS_ID, 6, 1, "error     ");
                        }
                        else if (item.value_i == MQTT_CONNECTION_OFF_LONG)
                        {
                                set_to_screen(SCREEN_STATUS_ID, 6, 1, "error (>5)");
                        }
                }
        }
        else if(item.sensor_id == TERM_ID)
        {
                if(item.type_id == TYPE_TERM_MODE)
                {
                        if (item.value_s.length() != 4)
                        {
                                set_to_screen(SCREEN_MAIN_ID, 16, 1, item.value_s + " ");
                        }
                        else
                        {
                                set_to_screen(SCREEN_MAIN_ID, 16, 1, item.value_s);
                        }
                }
                else if(item.type_id == TYPE_TERM_TEMP)
                {
                        if (item.value_s.length() != 2)
                        {
                                set_to_screen(SCREEN_MAIN_ID, 16, 2, String(item.value_i) + " ");
                        }
                        else
                        {
                                set_to_screen(SCREEN_MAIN_ID, 16, 2, String(item.value_i));
                        }
                }
        }
        else if(item.sensor_id == BUTTON1_ID)
        {
                if (current_screen > 0)
                {
                        current_screen--;
                        print_screen(current_screen);
                }
        }
        else if(item.sensor_id == BUTTON2_ID)
        {
                if (current_screen < SCREEN_NUMBER - 1)
                {
                        current_screen++;
                        print_screen(current_screen);
                }
        }

        return;
}
