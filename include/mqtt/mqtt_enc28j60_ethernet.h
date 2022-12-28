#ifndef __MQTT_ETH_H__
#define __MQTT_ETH_H__

#include <EthernetENC.h>

#include <inttypes.h>

#include "mqtt.h"

/**
 * \brief MQTT ENC ethernet driver
 * 
 * This class extends the \ref Mqtt class with the required Ethernet functionality. This class is specifically designed
 * to work with the ENC28J60, controlled using SPI.
 */
class MqttEnc28J60Ethernet : public Mqtt
{
public:

	/**
	 * MqttEnc28J60Ethernet constructor initializing the mqtt driver. It takes the name which is required for the mqtt broker, 
	 * the mac address of the Ethernet shield and the slave select pin for the SPI interface.
	 * 
	 * \param name Name of the device
	 * \param mac The mac adress
	 * \param slaveSelectPin The slave select pin
	 */
	MqttEnc28J60Ethernet(const char *name, uint8_t mac[6], int slaveSelectPin);
private:
    bool initializeIfNotInitialized() override;

private:
    bool m_initialized;
	EthernetClient _ethClient;
	uint8_t _mac[6];
};

#endif