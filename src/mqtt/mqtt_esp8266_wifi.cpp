#include "mqtt/mqtt_esp8266_wifi.h"
#include "domotics_debug.h"

#include <WiFiEsp.h>

MqttEsp8266Wifi::MqttEsp8266Wifi(const char * name, Stream * wifiStream, const char * ssid, const char * password) :
    Mqtt(name, _wifiClient), m_initialized(false), _ssid(ssid), _password(password), _stream(wifiStream)
{
}

bool MqttEsp8266Wifi::initializeIfNotInitialized()
{
    if (m_initialized)
        return true;

    WiFiEspClass::init(_stream);

    if (WL_DISCONNECTED != WiFi.status())
        return false;

    if (WiFi.begin(_ssid, _password) != WL_CONNECTED)
    {
        DEBUG_PRINTLN("WiFi connection failed");
        return false;
    }

    DEBUG_PRINTLN("Connected to WiFi network successfully");
    DEBUG_PRINT("LocalIP: ");
    DEBUG_PRINTLN(WiFi.localIP());

    return true;
}