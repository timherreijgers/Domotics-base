#ifndef __MQTT_WIFI_H__
#define __MQTT_WIFI_H__

#ifndef DOMOTICS_DEBUG_LOG_ENABLED
#define _ESPLOGLEVEL_ 0
#endif

#include <Arduino.h>
#include <WiFiEspClient.h>

#include "mqtt.h"

/**
 * \brief MQTT Esp8266 WiFi driver
 * 
 * This class extends the \ref Mqtt class with the required WiFi functionality. This class is specifically designed
 * to work with the ESP8266, controlled over UART using AT commands. 
 */
class MqttEsp8266Wifi : public Mqtt
{
public:

	/**
	 * MqttEsp8266Wifi constructor initializing the mqtt driver. It takes the name which is required for the mqtt broker, a 
	 * stream to communicate with the hardware (probably a HardwareSerial or SoftwareSerial) and the SSID and password for the
	 * WiFi network. 
	 * 
	 * \param name Name of the device
	 * \param wifiStream Stream for hardware communication
	 * \param ssid Network name
	 * \param password Network password
	 */
	MqttEsp8266Wifi(const char *name, Stream *wifiStream, const char *ssid, const char *password);

	bool connect(const IPAddress &brokerIp) override;

private:
	const char *_ssid;
	const char *_password;
	Stream *_stream;
	WiFiEspClient _wifiClient;
};

#endif