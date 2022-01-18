#include "wifi_client.h"

static byte mqtt_server[] = {1, 1, 1, 1};
static int mqtt_port = 1883;

static WiFiClient wifi_client;
static PubSubClient mqtt_client(wifi_client);

static queue_item mqtt_callback_result;
static bool mqtt_callback_get;

static int mqtt_disconnect_timer;

// Local functions: MQTT

String mqtt_make_topic(queue_item &item)
{
        if (item.sensor_id == BME_ID)
        {
                switch (item.type_id)
                {
                case TYPE_TEMP:
                        return MQTT_PUB_10_0;
                case TYPE_HUM:
                        return MQTT_PUB_10_1;
                case TYPE_PRES:
                        return MQTT_PUB_10_2;
                
                
                default:
                        break;
                }
        }
        else if(item.sensor_id == TERM_ID)
        {
                if (item.type_id == TYPE_TERM_MODE)
                {
                        return MQTT_PUB_15_0S;
                }
                else if (item.type_id == TYPE_TERM_TEMP)
                {
                        return MQTT_PUB_15_1S;
                }
        }
        else if(item.sensor_id == PIR_ID)
        {
                return MQTT_PUB_21;
        }
        else if(item.sensor_id == PHOTO_ID)
        {
                return MQTT_PUB_20;
        }

        return "";
}

queue_item mqtt_from_topic(String &topic, String value)
{
        queue_item item;
        item.board_id = THIS_BOARD_ID;

        if (topic == MQTT_SUB_15_1C)
        {
                item.sensor_id = TERM_ID;
                item.type_id = TYPE_TERM_TEMP;
                item.value_type = VALUE_TYPE_I;
                item.value_i = value.toInt();
        }
        else if (topic == MQTT_SUB_15_0C)
        {
                item.sensor_id = TERM_ID;
                item.type_id = TYPE_TERM_MODE;
                item.value_type = VALUE_TYPE_S;
                item.value_s = value.c_str();
        }

        mqtt_callback_get = true;

        return item;
}

void mqtt_callback(const char* topic, byte* payload, unsigned int length)
{
        String top = String(topic);
        String value;
        for (unsigned int i = 0; i < length; i++)
        {
                value += (char)payload[i];
        }

        mqtt_callback_result = mqtt_from_topic(top, value);

        return;
}

void mqtt_subscribe()
{
        mqtt_client.subscribe(MQTT_SUB_15_0C);
        mqtt_client.subscribe(MQTT_SUB_15_1C);

        return;
}

// Global functions

bool wifi_init()
{
        Serial.println();
        Serial.println(F("===== WiFi init ====="));

        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASS);

        Serial.print(F("connecting ... "));
        while (WiFi.status() != WL_CONNECTED)
        {
                delay(500);
        }
        Serial.print(F("connected (status: "));
        Serial.print(WiFi.status());
        Serial.println(")");
        Serial.print(F("MAC address: "));
        Serial.println(WiFi.macAddress());
        Serial.print(F("IP address: "));
        Serial.println(WiFi.localIP());
        Serial.print(F("gateway: "));
        Serial.println(WiFi.gatewayIP());
        Serial.print(F("subnet mask: "));
        Serial.println(WiFi.subnetMask());

        WiFi.setAutoReconnect(true);
        WiFi.persistent(true);

        Serial.println(F("===== eof  init ====="));
        Serial.println();

        return true;
}

bool mqtt_init()
{
        Serial.println();
        Serial.println(F("===== MQTT init ====="));

        mqtt_client.setServer(mqtt_server, mqtt_port);
        mqtt_client.setCallback(mqtt_callback);

        Serial.print(F("connecting ... "));
        while (!mqtt_client.connected())
        {
                if (mqtt_client.connect(MQTT_HOSTNAME))
                {
                        Serial.println("connected");
                        mqtt_subscribe();
                        continue;
                }
                else
                {
                        delay(500);
                }
        }

        mqtt_callback_get = false;
        mqtt_disconnect_timer = millis();

        Serial.println(F("===== eof  init ====="));

        return true;
}

bool wifi_is_conn()
{
        return (WiFi.status() == WL_CONNECTED);
}

bool mqtt_is_conn()
{
        return mqtt_client.connected();
}

bool mqtt_reconn()
{
        if (mqtt_client.connect(MQTT_HOSTNAME))
        {
                mqtt_subscribe();
        }
        
        return mqtt_client.connected();
}

queue_item wifi_status()
{
        queue_item item;
        item.sensor_id = WIFI_ID;
        item.value_type = VALUE_TYPE_I;
        item.value_i = (WiFi.status() == WL_CONNECTED);

        return item;
}

queue_item mqtt_status()
{
        queue_item item;
        item.sensor_id = MQTT_ID;
        item.value_type = VALUE_TYPE_I;
        item.value_i = mqtt_client.connected();

        if (mqtt_client.connected())
        {
                mqtt_disconnect_timer = millis();
                item.value_i = MQTT_CONNECTION_ON;
        }
        else if (!mqtt_client.connected())
        {
                if (millis() - mqtt_disconnect_timer < CONNECTION_TIMER)
                {
                        item.value_i = MQTT_CONNECTION_OFF;
                }
                else if (millis() - mqtt_disconnect_timer > CONNECTION_TIMER)
                {
                        item.value_i = MQTT_CONNECTION_OFF_LONG;
                }

        }

        return item;
}

void mqtt_send(queue_item &item)
{
        if (item.value_type == VALUE_TYPE_I)
        {
                mqtt_client.publish(mqtt_make_topic(item).c_str(), String(item.value_i).c_str());
        }
        else if (item.value_type == VALUE_TYPE_F)
        {
                mqtt_client.publish(mqtt_make_topic(item).c_str(), String(item.value_f).c_str());
        }
        else if (item.value_type == VALUE_TYPE_S)
        {
                mqtt_client.publish(mqtt_make_topic(item).c_str(), item.value_s.c_str());
        }
}

void mqtt_update()
{
        mqtt_client.loop();

        return;
}

queue_item mqtt_recieve()
{
        mqtt_callback_get = false;

        return mqtt_callback_result;
}

bool is_mqtt_result()
{
        return mqtt_callback_get;
}
