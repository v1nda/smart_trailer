#ifndef CLIMATE_H
#define CLIMATE_H

#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include "Wire.h"
#include "queue.h"

#define TERM_MODE_OFF "off"
#define TERM_MODE_HEAT "heat"

#define SEALEVELPRESSURE_HPA (162.0)

#define HEATING_RANGE 2

void climate_init();

void climate_sensor_renew();
queue_item climate_get_temp(byte index);
queue_item climate_get_hum(byte index);
queue_item climate_get_pressure(byte index);

void climate_term_mode_set(queue_item &item);
void climate_term_temp_set(queue_item &item);

queue_item climate_term_mode_status();
queue_item climate_term_temp_status();

queue_item climate_term_count();

#endif