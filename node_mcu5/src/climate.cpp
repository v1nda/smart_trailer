#include "climate.h"

static Adafruit_BME280 bme;

static float temper[CLIMATE_SENSOR_NUMBER];
static float hum[CLIMATE_SENSOR_NUMBER];
static float pressure[CLIMATE_SENSOR_NUMBER];

static String termostat_mode;
static int termostat_value;

// Local functions

void renew_bme_values(Adafruit_BME280 &_bme, byte index)
{
        float result_temp = _bme.readTemperature();
        float result_hum = _bme.readHumidity();
        float result_pres = _bme.readPressure() * 0.00750062;
        

        if (isnan(result_temp) || isnan(result_hum) || isnan(result_pres))
        {
                temper[index - CLIMATE_ID_SUB] = -273;
                hum[index - CLIMATE_ID_SUB] = 0;
                pressure[index - CLIMATE_ID_SUB] = 0;
                return;
        }

        temper[index - CLIMATE_ID_SUB] = result_temp;
        hum[index - CLIMATE_ID_SUB] = result_hum;
        pressure[index - CLIMATE_ID_SUB] = result_pres;

        return;
}

void bme_init()
{
        bme.begin(BME_ADDRESS);

        return;
}

void termostat_init()
{
        termostat_mode = TERM_MODE_OFF;
        termostat_value = 20;

        return;
}

// Global functions

void climate_init()
{
        bme_init();
        termostat_init();
}

void climate_sensor_renew()
{
        renew_bme_values(bme, BME_ID);

        return;
}

queue_item climate_get_temp(byte index)
{
        queue_item item;
        item.sensor_id = index;
        item.type_id = TYPE_TEMP;
        item.value_type = VALUE_TYPE_F;
        item.value_f = temper[index - CLIMATE_ID_SUB];
        
        return item;
}

queue_item climate_get_hum(byte index)
{
        queue_item item;
        item.sensor_id = index;
        item.type_id = TYPE_HUM;
        item.value_type = VALUE_TYPE_F;
        item.value_f = hum[index - CLIMATE_ID_SUB];
        
        return item;
}

queue_item climate_get_pressure(byte index)
{
        queue_item item;
        item.sensor_id = index;
        item.type_id = TYPE_PRES;
        item.value_type = VALUE_TYPE_F;
        item.value_f = pressure[index - CLIMATE_ID_SUB];
        
        return item;
}

void climate_term_mode_set(queue_item &item)
{
        termostat_mode = item.value_s;

        return;
}

void climate_term_temp_set(queue_item &item)
{
        termostat_value = item.value_i;

        return;
}

queue_item climate_term_mode_status()
{
        queue_item item;
        item.sensor_id = TERM_ID;
        item.type_id = TYPE_TERM_MODE;
        item.value_type = VALUE_TYPE_S;
        item.value_s = termostat_mode;

        return item;
}

queue_item climate_term_temp_status()
{
        queue_item item;
        item.sensor_id = TERM_ID;
        item.type_id = TYPE_TERM_TEMP;
        item.value_type = VALUE_TYPE_I;
        item.value_i = termostat_value;

        return item;
}

queue_item climate_term_count()
{
        queue_item item;
        item.sensor_id = TERM_ID;
        item.type_id = TYPE_TERM_RELAY;
        item.value_type = VALUE_TYPE_I;
        item.value_i = termostat_value;

        if (termostat_mode == TERM_MODE_HEAT)
        {
                if ((int)temper[BME_ID - CLIMATE_ID_SUB] < (termostat_value - (HEATING_RANGE / 2)))
                {
                        item.value_i = true;
                }
                else if ((int)temper[BME_ID - CLIMATE_ID_SUB] > (termostat_value + (HEATING_RANGE / 2)))
                {
                        item.value_i = false;
                }
        }
        else if (termostat_mode == TERM_MODE_OFF)
        {
                item.value_i = false;
        }

        return item;
}
