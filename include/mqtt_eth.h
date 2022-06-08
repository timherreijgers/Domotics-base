#ifndef __MQTT_ETH_H__
#define __MQTT_ETH_H__

#include <EthernetENC.h>

#include <inttypes.h>

#include "mqtt.h"

/**
 * MQTT Ethernet driver
 */
class MqttEthernet : public Mqtt
{
public:
	MqttEthernet(const char *name, uint8_t mac[6], int slaveSelectPin);

	bool connect(const IPAddress &brokerIp) override;

private:
	EthernetClient _ethClient;
	uint8_t _mac[6];
};

#endif