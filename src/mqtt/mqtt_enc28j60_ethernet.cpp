#include "mqtt/mqtt_enc28j60_ethernet.h"
#include "domotics_debug.h"

#include <EthernetENC.h>
#include <stdlib.h>


MqttEnc28J60Ethernet::MqttEnc28J60Ethernet(const char * name, uint8_t mac[6], int slaveSelectPin) :
    Mqtt(name, _ethClient), m_initialized(false)
{
    memcpy(_mac, mac, 6);
    Ethernet.init(slaveSelectPin);
}

bool MqttEnc28J60Ethernet::connect(const IPAddress & brokerIp)
{
    Ethernet.begin(_mac);

    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        DEBUG_PRINTLN("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true)
            ;
    }

    delay(100);

    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println(F("Ethernet cable is not connected."));
    }

    DEBUG_PRINTLN("Connected to Ethernet");
    DEBUG_PRINT("LocalIP: ");
    DEBUG_PRINTLN(Ethernet.localIP());

    DEBUG_PRINTLN("Connecting to MQTT broker");
    bool res = connectToBroker(brokerIp);
    DEBUG_PRINTLN("Connected to broker");

    return res;
}

bool MqttEnc28J60Ethernet::initializeIfNotInitialized()
{
    if(m_initialized)
        return true;

    Ethernet.begin(_mac);

    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        DEBUG_PRINTLN("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        return false;
    }

    delay(100);

    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println(F("Ethernet cable is not connected."));
        return false;
    }

    DEBUG_PRINTLN("Connected to Ethernet");
    DEBUG_PRINT("LocalIP: ");
    DEBUG_PRINTLN(Ethernet.localIP());

    m_initialized = true;
    return true;
}