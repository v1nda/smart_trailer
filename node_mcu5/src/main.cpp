#include "timer.h"
#include "climate.h"
#include "wifi_client.h"
#include "lcd.h"
#include "button.h"
#include "light.h"
#include "relay.h"

Queue input_que;

void input_que_processing(queue_item item)
{
        if (item.sensor_id == BME_ID)
        {
                mqtt_send(item);
                lcd_set(item);
        }
        else if (item.sensor_id == WIFI_ID)
        {
                lcd_set(item);
        }
        else if (item.sensor_id == MQTT_ID)
        {
                lcd_set(item);
                if (item.value_i == MQTT_CONNECTION_ON)
                {
                        relay_unlock();
                }
                else if (item.value_i == MQTT_CONNECTION_OFF_LONG)
                {
                        relay_lock();
                }
        }
        else if (item.sensor_id == TERM_ID)
        {
                if (item.type_id == TYPE_TERM_MODE)
                {
                        climate_term_mode_set(item);
                        mqtt_send(item);
                        lcd_set(item);
                }
                else if (item.type_id == TYPE_TERM_TEMP)
                {
                        climate_term_temp_set(item);
                        mqtt_send(item);
                        lcd_set(item);
                }
                else if (item.type_id == TYPE_TERM_RELAY)
                {
                        relay_set(item.value_i);
                }
        }
        else if (item.sensor_id == PIR_ID)
        {
                mqtt_send(item);
        }
        else if (item.sensor_id == PHOTO_ID)
        {
                mqtt_send(item);
        }
        else if (item.sensor_id == BUTTON1_ID && item.value_i)
        {
                lcd_set(item);
        }
        else if (item.sensor_id == BUTTON2_ID && item.value_i)
        {
                lcd_set(item);
        }

        return;
}

void setup()
{
        Serial.begin(115200);

        lcd_preinit();

        if (wifi_init())
        {
                lcd_init_print(F("WiFi ... done."));
        }
        if (mqtt_init())
        {
                lcd_init_print(F("MQTT ... done."));
        }

        relay_init();
        
        button_init();
        climate_init();
        input_que.enqueue(climate_term_mode_status());
        input_que.enqueue(climate_term_temp_status());

        delay(1000);
        lcd_init();

        timers_init();

        return;
}

void loop()
{
        button_renew();
        if (is_tap() && button_wake_up())
        {
                input_que.enqueue(button_get_item(BUTTON1_ID));
                input_que.enqueue(button_get_item(BUTTON2_ID));
        }

        light_sensors_renew();
        light_count();

        if (!mqtt_is_conn() && is_time(TIMER_10S))
        {
                mqtt_reconn();
        }

        if (is_time(TIMER_1S))
        {
                input_que.enqueue(wifi_status());
                input_que.enqueue(mqtt_status());

                input_que.enqueue(light_get_photo());
                input_que.enqueue(light_get_move());

                input_que.enqueue(climate_term_count());
        }


        if (is_time(TIMER_5S))
        {
                climate_sensor_renew();
                input_que.enqueue(climate_get_temp(BME_ID));
                input_que.enqueue(climate_get_hum(BME_ID));
                input_que.enqueue(climate_get_pressure(BME_ID));
        }

        if (!input_que.is_empty())
        {
                input_que_processing(input_que.dequeue());
        }

        mqtt_update();        
        if (is_mqtt_result())
        {
                input_que.enqueue(mqtt_recieve());
        }

        return;
}