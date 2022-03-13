#ifndef __MQTT_H__
#define __MQTT_H__

#include "PubSubClient.h"
#include <Arduino.h>
#include <IPAddress.h>

void mqttMessageReceived(const char *topic, const uint8_t *payload, uint32_t length);

class Mqtt
{
public:	
    ~Mqtt();

    bool publishOnTopic(const char *topic, const char *payload);
	bool subscribeToTopic(const char *topic);

	virtual bool connect(const IPAddress &brokerIp) = 0;

	bool loop();
protected:
	bool connectToBroker(const IPAddress &brokerIp);
    Mqtt(const char *name, Client &client);
private:
    const char *m_name;
    PubSubClient m_mqttClient;
};

#endif