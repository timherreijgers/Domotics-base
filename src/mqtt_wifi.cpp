#include "mqtt_wifi.h"
#include "domotics_debug.h"
#include "WiFiEsp.h"

MqttWifi::MqttWifi(const char *name, Stream *wifiStream, const char *ssid, const char *password): Mqtt(name, _wifiClient), _ssid(ssid), _password(password), _stream(wifiStream)
{
}

bool MqttWifi::connect(const IPAddress &brokerIp)
{
	WiFi.init(_stream);

	if(WiFi.begin(_ssid, _password) != WL_CONNECTED)
	{
		DEBUG_PRINTLN("WiFi connection failed");
		return false;
	}

	DEBUG_PRINTLN("Connected to WiFi network successfully");
	DEBUG_PRINT("LocalIP: ");
	DEBUG_PRINTLN(WiFi.localIP());

	DEBUG_PRINTLN("Connecting to MQTT broker");
	bool res = connectToBroker(brokerIp);
	DEBUG_PRINTLN("Connected to broker");

	return res;
}