#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>



const char apn[] = "safaricom";  
const char user[] = "";        
const char pass[] = "";         
const char broker[] = "192.168.2.5";  
const char topic[] = "test/topic";


#define SIM800L_RX 12  
#define SIM800L_TX 13  // Connect to SIM800L RX

SoftwareSerial sim800lSerial(SIM800L_RX, SIM800L_TX);
TinyGsm modem(sim800lSerial);
TinyGsmClient gsmClient(modem);
PubSubClient mqttClient(gsmClient);



void connectToMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("ESP32_Client")) {
      Serial.println("Connected!");
      mqttClient.subscribe(topic);  // Subscribe to the topic
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void espPiComms() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.loop();
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 10000) {
    lastMsg = millis();
    String msg = "Hello from ESP32 with SIM800L!";
    mqttClient.publish(topic, msg.c_str());
    Serial.println("Message sent: " + msg);
  }
}
