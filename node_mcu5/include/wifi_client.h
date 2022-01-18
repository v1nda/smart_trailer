#ifndef WIFI_CLIENT_H
#define WIFI_CLIENT_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include "queue.h"

#define WIFI_SSID "ssid"
#define WIFI_PASS "password"

#define MQTT_HOSTNAME "node_mcu5"

#define CONNECTION_TIMER 50000

bool wifi_init();
bool mqtt_init();

bool wifi_is_conn();
bool mqtt_is_conn();
bool mqtt_reconn();

queue_item wifi_status();
queue_item mqtt_status();

void mqtt_send(queue_item &item);
void mqtt_update();
queue_item mqtt_recieve();
bool is_mqtt_result();

#endif