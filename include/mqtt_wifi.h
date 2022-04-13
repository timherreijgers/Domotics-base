#ifndef __MQTT_WIFI_H__
#define __MQTT_WIFI_H__

#ifndef DOMOTICS_DEBUG_LOG_ENABLED
#define _ESPLOGLEVEL_ 0
#endif

#include <Arduino.h>
#include <WiFiEspClient.h>

#include "mqtt.h"

//TODO: Add callback to get updates about current state to drive something like LEDs
class MqttWifi : public Mqtt
{
public:
	MqttWifi(const char *name, Stream *wifiStream, const char *ssid, const char *password);

	bool connect(const IPAddress &brokerIp) override;

private:
	const char *_ssid;
	const char *_password;
	Stream *_stream;
	WiFiEspClient _wifiClient;
};

#endif