#ifndef __MQTT_H__
#define __MQTT_H__

/**
 * \file mqtt.h
 * 
 * File containing the MQTT middleware
 */

#include "PubSubClient.h"
#include <Arduino.h>
#include <IPAddress.h>

/**
 * Application callback which is called when disconnected from the MQTT broker. This callback should be
 * implemented in the application to handle disconnects. These disconnects can happen, for example, when
 * the DHCP lease ends and a new IP must be requested. When this happens the function \ref Mqtt::connect
 * should be called again to reinitialize and reconnect.
 */
void mqttDisconnected();

/**
 * Application callback, which is called when an MQTT message is received. This callback should
 * be implemented in the application to handle received messages. If this is not required, the callback
 * doens't have to be implemented. 
 * 
 * \param topic The topic of the received message
 * \param payload The received payload
 * \param length The length of the received payload
 */
void mqttMessageReceived(const char *topic, const uint8_t *payload, uint32_t length);

/**
 * \brief Base class for MQTT communication
 * 
 * This class provides the base functionality to enable MQTT communication and contains all logic to do with MQTT.
 * All connection logic is contained within the \ref MqttEthernet and \ref MqttEsp8266Wifi classes. One of these classes should
 * be used, depending on the hardware used. To actually send/receive messages, as well as keeping the connection alive, the 
 * Mqtt::poll() methods should be called periodically 
 * 
 * 
 * To enable more ways to communicate
 * with connection hardware, for example a different ethernet controller, this class can be extended. The hardware abstraction should
 * provide a <a href="https://www.arduino.cc/reference/en/libraries/wifi/">Client</a>. This Client is used as an interface between 
 * the hardware and the MQTT middleware. This Client has to be passed to the Mqtt::Mqtt(const char *, Client &) constructor.
 * The Client passed to the MQTT middleware <u>CAN NOT</u> go out of scope, as a reference to this object is saved. Besides 
 * the constructor, only the Mqtt::connect(const IPAddress &)method should be implemented. This method should connect to the
 * broker using the chosen hardware, after which it should call Mqtt::connectToBroker(const IPAddress &)to let the base class
 * establish the actual connection to the broker. 
 * 
 */
class Mqtt
{
public:	
    ~Mqtt();

	/**
	 * Publishes a payload in a topic. As the payload is in the style of a C-style string, the payload has to be 
	 * NULL terminated. If publishing the payload succeeds, this function will return true. If not, it will return false.
	 * 
	 * \param topic The topic to publish to
	 * \param payload The payload to publish
	 * 
	 * \returns True if successful, false otherwise
	 */
    bool publishOnTopic(const char *topic, const char *payload);

	/**
	 * Subscribes to a topic. To receive the messages, the function ::mqttMessageReceived(const char *, const uint8_t *, uint32_t) must be implemented.
	 * If subscribing to the topic succeeds, this function will return true. If not, it will return false.
	 * 
	 * \param topic The topic to subscribe to
	 * 
	 * \returns True if successful, false otherwise
	 */
	bool subscribeToTopic(const char *topic);

	/**
	 * Connect to the broker using the specified broker IP address. 
	 * If connecting to the broker succeeds, this function will return true. If not, it will return false.
	 * 
	 * \param brokerIp The broker IP address
	 * 
	 * \returns True if successful, false otherwise
	 */
	virtual bool connect(const IPAddress &brokerIp) = 0;

	/**
	 * Poll function for MQTT. Calling this function periodically is required to keep the connection alive. It's also 
	 * required to receive message. If polling is successful, this function return true. If not, it will return false.
	 *
	 * \returns True if successful, false otherwise
	 */
	bool loop();
protected:

	/**
	 * Connect to the broker using the initialized hardware interface. 
	 * If connecting to the broker succeeds, this function will return true. If not, it will return false.
	 * 
	 * \param brokerIp The broker IP address
	 * 
	 * \returns True if successful, false otherwise
	 */
	bool connectToBroker(const IPAddress &brokerIp);

	/**
	 * Mqtt constructor initializing the mqtt middleware. It takes the name which is required for the mqtt broker, as well as
	 * a reference to the client to read and write data to and from the hardware. Most hardware libraries (like for a library for a
	 * specific ethernet module) will provide this client, given it's created for the Arduino ecosystem. 
	 * 
	 * \note The client must not go out of scope, as a reference to this client is saved in the utilized mqtt library. 
	 * 
	 * \param name Name of the device
	 * \param client The client 
	 */
    Mqtt(const char *name, Client &client);
private:
    const char *m_name;
    PubSubClient m_mqttClient;
};

#endif