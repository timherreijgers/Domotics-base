#include "mqtt/mqtt.h"
#include "domotics_debug.h"

#include <string.h>

static void onMessageReceived(char * topic, uint8_t * payload, unsigned int length);

Mqtt::Mqtt(const char * name, Client & client) :
    m_name(name)
{
    m_mqttClient = PubSubClient(client);
}

Mqtt::~Mqtt()
{
    if (m_mqttClient.connected())
        m_mqttClient.disconnect();
}

void Mqtt::addStatusMessage(const char * statusTopic, const char * onlineStatusMessage, const char * offlineStatusMessage)
{
    m_statusTopic = statusTopic;
    m_onlineStatusMessage = onlineStatusMessage;
    m_offlineStatusMessage = offlineStatusMessage;
}

bool Mqtt::publishOnTopic(const char * topic, const char * payload)
{
    if (!m_mqttClient.connected())
        return false;

    return m_mqttClient.publish(topic, payload);
}

bool Mqtt::connectToBroker(const IPAddress & brokerIp)
{
    m_mqttClient.setServer(brokerIp, 1883);
    m_mqttClient.setCallback(onMessageReceived);
    m_mqttClient.setKeepAlive(5);

    if(m_statusTopic == nullptr)
    {
        while (!m_mqttClient.connect(m_name))
        {
            DEBUG_PRINT(".");
            delay(1000);
        }
        DEBUG_PRINTLN("");
    }
    else
    {
        while (!m_mqttClient.connect(m_name, m_statusTopic, 0, 1, m_offlineStatusMessage))
        {
            DEBUG_PRINT(".");
            delay(1000);
        }
        DEBUG_PRINTLN("");
        publishOnTopic(m_statusTopic, m_onlineStatusMessage);
    }

    return true;
}

bool Mqtt::subscribeToTopic(const char * topic)
{
    return m_mqttClient.subscribe(topic);
}

bool Mqtt::connect(const IPAddress & brokerIp)
{
    const auto initialized = initializeIfNotInitialized();

    DEBUG_PRINTLN("Connecting to MQTT broker");
    const auto connected = connectToBroker(brokerIp);
    DEBUG_PRINTLN("Connected to broker");

    return initialized & connected;
}

bool Mqtt::loop()
{
    if (!m_mqttClient.connected())
    {
        DEBUG_PRINT("Not connected, error code: ");
        DEBUG_PRINTLN(m_mqttClient.state());
        mqttDisconnected();
        return false;
    }

    return m_mqttClient.loop();
}

static void onMessageReceived(char * topic, uint8_t * payload, unsigned int length)
{
    mqttMessageReceived(topic, payload, length);
}

__attribute__((weak)) void mqttMessageReceived(const char * topic, const uint8_t * payload, uint32_t length)
{
}

__attribute__((weak)) void mqttDisconnected()
{
}