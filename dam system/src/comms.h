#define TINY_GSM_MODEM_SIM800 
#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char apn[] = "safaricom";  // Set your APN
const char user[] = "";         // Leave empty if no user is required
const char pass[] = "";         // Leave empty if no password is required

// MQTT server details
const char* mqttServer = "your_mqtt_broker_address";
const int mqttPort = 1883;
const char* mqttUser = "your_mqtt_username"; // Leave empty if no username is required
const char* mqttPassword = "your_mqtt_password"; // Leave empty if no password is required

// Topic
const char* topic = "test/arduino";

TinyGsm modem(Serial3);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

void connectToMqtt() {
  while (!mqtt.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqtt.connect("MegaClient", mqttUser, mqttPassword)) {
      Serial.println(" connected");
      mqtt.subscribe(topic);
    } else {
      Serial.print(" failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}