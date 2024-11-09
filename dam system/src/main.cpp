#include <Arduino.h>
#include "loadcell.h"
#include "comms.h"

void setup() {
  //general configuration
  Serial.begin(115200); 

  //gsm and mqtt configuration
  sim800lSerial.begin(9600);
  delay(3000);
  Serial.println("Initializing modem...");
  modem.restart();
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println("Failed to connect to GPRS");
    return;
  }
  Serial.println("Connected to GPRS");

  // Set up the MQTT client
  mqttClient.setServer(broker, 1883);
  mqttClient.setCallback(mqttCallback);
  connectToMqtt();

  //loadcell configuration
  delay(10);
  LoadCell.begin();
  float calibrationValue; 
  calibrationValue = 761.31; 
  unsigned long stabilizingtime = 2000; 
  boolean _tare = true; 
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); 
    delay(100);
    
  }
  delay(1000);
  LoadCell.tareNoDelay();
}

void loop() {
  espPiComms();
  //damMass();

}