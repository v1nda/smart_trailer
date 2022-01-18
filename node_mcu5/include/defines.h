#ifndef DEFINES_H
#define DEFINES_H

#define THIS_BOARD_ID 5

// WiFi and MQTT

#define WIFI_ID 100
#define MQTT_ID 101

#define MQTT_CONNECTION_OFF 0
#define MQTT_CONNECTION_ON 1
#define MQTT_CONNECTION_OFF_LONG 2

#define MQTT_PUB_10_0 "/nodemcu5/climate/10/temp"
#define MQTT_PUB_10_1 "/nodemcu5/climate/10/hum"
#define MQTT_PUB_10_2 "/nodemcu5/climate/10/pressure"

#define MQTT_PUB_15_0S "/nodemcu5/termostate/mode/state"
#define MQTT_SUB_15_0C "/nodemcu5/termostate/mode/command"
#define MQTT_PUB_15_1S "/nodemcu5/termostate/temp/state"
#define MQTT_SUB_15_1C "/nodemcu5/termostate/temp/command"

#define MQTT_PUB_21 "/nodemcu5/light/move"
#define MQTT_PUB_20 "/nodemcu5/light/photo"

// Climate

#define BME_ADDRESS 0x76

#define CLIMATE_SENSOR_NUMBER 1
#define BME_ID 10
#define CLIMATE_ID_SUB 10

#define TYPE_TEMP 0
#define TYPE_HUM 1
#define TYPE_PRES 2

#define TERM_ID 15

#define TYPE_TERM_MODE 0
#define TYPE_TERM_TEMP 1
#define TYPE_TERM_RELAY 2

// Light

#define PHOTO_PIN D7
#define PIR_PIN D8

#define PHOTO_ID 20
#define PIR_ID 21

// Buttons

#define BUTTON1_PIN D5
#define BUTTON2_PIN D6

#define BUTTON_NUMBER 2
#define BUTTON1_ID 30
#define BUTTON2_ID 31
#define BUTTON_ID_SUB 30

// Relay

#define RELAY1_PIN D4

// Lcd

#define LCD_ADDRESS 0x27

#endif