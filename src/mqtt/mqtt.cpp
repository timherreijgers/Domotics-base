#include "mqtt/mqtt.h"
#include "domotics_debug.h"

#include <string.h>

static constexpr uint8_t MAX_ATTEMPTS = 10;

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

void Mqtt::addStatusMessage(const char * statusTopic)
{
    addStatusMessage(statusTopic, "online", "offline");
}

bool Mqtt::publishOnTopic(const char * topic, const char * payload, bool retain)
{
    if (!m_mqttClient.connected())
        return false;

    return m_mqttClient.publish(topic, payload, retain);
}

bool Mqtt::connectToBroker(const IPAddress & brokerIp)
{
    uint8_t attempts = 0;
    m_mqttClient.setServer(brokerIp, 1883);
    m_mqttClient.setCallback(onMessageReceived);
    m_mqttClient.setKeepAlive(5);

    const auto connectFunction = m_statusTopic == nullptr ?
                                 [](Mqtt * mqtt){return mqtt->m_mqttClient.connect(mqtt->m_name);} :
                                 [](Mqtt * mqtt){return mqtt->m_mqttClient.connect(mqtt->m_name, mqtt->m_statusTopic, 0, 1, mqtt->m_offlineStatusMessage);};

    while(!connectFunction(this) && attempts < MAX_ATTEMPTS)
    {
        DEBUG_PRINT(".");
        delay(1000);
        attempts++;
    }

    if (attempts >= MAX_ATTEMPTS)
        return false;

    if(m_statusTopic != nullptr)
        publishOnTopic(m_statusTopic, m_onlineStatusMessage, true);

    return true
}

bool Mqtt::subscribeToTopic(const char * topic)
{
    return m_mqttClient.subscribe(topic);
}

bool Mqtt::connect(const IPAddress & brokerIp)
{
    const auto initialized = initializeIfNotInitialized();
    if(!initialized)
        return false;

    DEBUG_PRINTLN("Connecting to MQTT broker");
    const auto connected = connectToBroker(brokerIp);
    DEBUG_PRINTLN("Connected to broker");

    return connected;
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